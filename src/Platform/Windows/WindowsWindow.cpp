#include "../../../../WindowSystem/include/WindowSystem/Events/Event.h"
#include "../../../../WindowSystem/include/WindowSystem/Events/KeyEvent.h"
#include "../../../../WindowSystem/include/WindowSystem/Input/KeypadCodes.h"
#include "InputTranslation/Keypad.h"
#include "../../../../WindowSystem/include/WindowSystem/Events/MouseEvent.h"
#include "../../../../WindowSystem/include/WindowSystem/Input/MouseCodes.h"
#include "InputTranslation/Mouse.h"
#include "../../../../WindowSystem/include/WindowSystem/Events/WindowEvent.h"
#include "../../Utils/Utf.h"
#include "StyleTranslation/Style.h"
#include "WindowsWindow.h"

static std::wstring Utf8ToUtf16(const std::string& utf8Str)
{
	if (utf8Str.empty()) {
		return std::wstring();
	}
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &utf8Str[0], (int)utf8Str.size(), NULL, 0);
	std::wstring wstr(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &utf8Str[0], (int)utf8Str.size(), &wstr[0], size_needed);
	return wstr;
}

// -----------------------------------------------------------------

WindowSystem::WindowsWindow::WindowsWindow(const WindowProps& props)
	: m_hwnd(nullptr), m_eventCallback([](WindowSystem::Event::Event&) {}), m_shouldClose(false)
{
	m_props = props;
	Init();
}

WindowSystem::WindowsWindow::~WindowsWindow()
{
	if (m_hwnd) {
		DestroyWindow(m_hwnd);
	}
}

void WindowSystem::WindowsWindow::SetEventCallback(const EventCallbackFn& callback)
{
	m_eventCallback = callback;
}

void WindowSystem::WindowsWindow::PollEvents()
{
	MSG msg;
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// WM_MOUSEWHEEL / WM_MOUSEHWHEEL
	if (m_accumulatedScroll != 0.f) {
		WindowSystem::Event::MouseScrolledEvent mse(m_accumulatedScroll.XOffset, m_accumulatedScroll.YOffset);
		m_eventCallback(mse);
		m_accumulatedScroll.ToZero();
	}
}

WindowSystem::WindowProps WindowSystem::WindowsWindow::GetProps() const
{
	return m_props;
}

void WindowSystem::WindowsWindow::SetTitle(const std::string& title)
{
	m_props.Title = title;
	SetWindowTextW(m_hwnd, Utf8ToUtf16(m_props.Title).c_str());
}

void WindowSystem::WindowsWindow::SetPosition(std::int32_t posX, std::int32_t posY)
{
	m_props.PosX = posX; m_props.PosY = posY;
	SetWindowPos(m_hwnd, NULL, posX, posY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void WindowSystem::WindowsWindow::SetRect(std::int32_t width, std::int32_t height)
{
	m_props.Width = width; m_props.Height = height;
	
	DWORD style = StyleToWindows(m_props);
	DWORD exStyle = ExStyleToWindows(m_props);
	RECT rect = { 0, 0, m_props.Width, m_props.Height };
	AdjustWindowRectEx(&rect, style, FALSE, exStyle);
	
	SetWindowPos(m_hwnd, NULL, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE | SWP_NOZORDER);
}

void WindowSystem::WindowsWindow::SetStyle(WindowStyle style)
{
	m_props.Style = style;

	//if (!m_hwnd) return;

	DWORD dwStyle = StyleToWindows(m_props);
	DWORD dwExStyle = ExStyleToWindows(m_props);

	SetWindowLongW(m_hwnd, GWL_STYLE, dwStyle);
	SetWindowLongW(m_hwnd, GWL_EXSTYLE, dwExStyle);

	HMENU hMenu = GetSystemMenu(m_hwnd, FALSE);
	if (hMenu) {
		if (HasFlag(style, WindowStyle::CloseButton)) {
			EnableMenuItem(hMenu, SC_CLOSE, MF_BYCOMMAND | MF_ENABLED);
		}
		else {
			EnableMenuItem(hMenu, SC_CLOSE, MF_BYCOMMAND | MF_GRAYED);
		}
	}
	DrawMenuBar(m_hwnd);

	if (HasFlag(style, WindowStyle::Transparent)) {
		SetLayeredWindowAttributes(m_hwnd, 0, m_props.Alpha, LWA_ALPHA);
	}

	HWND hWndInsertAfter = (HasFlag(style, WindowStyle::AlwaysOnTop)) ? HWND_TOPMOST : HWND_NOTOPMOST;
	SetWindowPos(m_hwnd, hWndInsertAfter, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_FRAMECHANGED);

	if (HasFlag(style, WindowStyle::Focused)) {
		SetForegroundWindow(m_hwnd);
		SetFocus(m_hwnd);
	}
}

void WindowSystem::WindowsWindow::SetAlpha(std::uint8_t alpha)
{
	alpha = (alpha < 0 ? 0 : (alpha < 255 ? alpha : 255));
	m_props.Alpha = alpha;
	SetStyle(m_props.Style);
}

void WindowSystem::WindowsWindow::SetWindowMode(WindowMode windowMode)
{
	if (m_props.Mode == windowMode)
		return;

	switch (windowMode) {
	case WindowMode::Windowed: {
		m_props.Style				= m_saveWindowState.Style;
		m_props.SpecStyle.Windows	= m_saveWindowState.SpecStyle;

		DWORD style		= StyleToWindows(m_props);
		DWORD exStyle	= ExStyleToWindows(m_props);

		SetWindowLongPtr(m_hwnd, GWL_STYLE, style);
		SetWindowLongPtr(m_hwnd, GWL_EXSTYLE, exStyle);
		
		m_props.Style = m_saveWindowState.Style;
		m_props.SpecStyle.Windows = m_saveWindowState.SpecStyle;

		RECT rect = { 0, 0, m_saveWindowState.Width, m_saveWindowState.Height };
		AdjustWindowRectEx(&rect, style, FALSE, exStyle);

		int x		= m_saveWindowState.PosX;
		int y		= m_saveWindowState.PosY;
		int width	= rect.right - rect.left;
		int height	= rect.bottom - rect.top;

		SetWindowPos(m_hwnd, nullptr, x, y, width, height, SWP_SHOWWINDOW | SWP_FRAMECHANGED);

		m_props.PosX	= x;
		m_props.PosY	= y;
		m_props.Width	= m_saveWindowState.Width;
		m_props.Height	= m_saveWindowState.Height;
		m_props.Mode = WindowMode::Windowed;
		
		break;
	}
	case WindowMode::BorderlessFullscreen: {

		if (m_props.Mode == WindowMode::Windowed) {
			m_saveWindowState = m_props;
		}

		HMONITOR hMonitor = MonitorFromWindow(m_hwnd, MONITOR_DEFAULTTONEAREST);
		MONITORINFO monitorInfo = { sizeof(MONITORINFO) };
		GetMonitorInfoW(hMonitor, &monitorInfo);
		
		SetStyle(WindowStyle::Popup | WindowStyle::Visible | WindowStyle::TaskbarIcon);

		DWORD style		= StyleToWindows(m_props);
		DWORD exStyle	= ExStyleToWindows(m_props);
		
		SetWindowLongPtr(m_hwnd, GWL_STYLE, style);
		SetWindowLongPtr(m_hwnd, GWL_EXSTYLE, exStyle);

		int x		= monitorInfo.rcMonitor.left;
		int y		= monitorInfo.rcMonitor.top;
		int width	= monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left;
		int height	= monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top;

		SetWindowPos(m_hwnd, HWND_TOP, x, y, width, height, SWP_SHOWWINDOW | SWP_FRAMECHANGED);

		m_props.PosX	= x;
		m_props.PosY	= y;
		m_props.Width	= width;
		m_props.Height	= height;
		m_props.Mode	= WindowMode::BorderlessFullscreen;
		
		break;
	}
	case WindowMode::ExclusiveFullscreen: {

		break;
	}
	}
}

void WindowSystem::WindowsWindow::SetSpecStyle(WindowProps::SpecStyleOS specStyle)
{
}

void WindowSystem::WindowsWindow::Minimize()
{
	ShowWindow(m_hwnd, SW_MINIMIZE);
}

void WindowSystem::WindowsWindow::Maximize()
{
	ShowWindow(m_hwnd, SW_MAXIMIZE);
}

void WindowSystem::WindowsWindow::Restore()
{
	ShowWindow(m_hwnd, SW_RESTORE);
}

void WindowSystem::WindowsWindow::Show()
{
	ShowWindow(m_hwnd, SW_SHOW);
}

void WindowSystem::WindowsWindow::Hide()
{
	ShowWindow(m_hwnd, SW_HIDE);
}

bool WindowSystem::WindowsWindow::IsKeyPressed(Input::KeypadCode key) const
{
	return m_inputState.KeypadState[+key];
}

bool WindowSystem::WindowsWindow::IsButtonPressed(Input::MouseCode button) const
{
	return m_inputState.MouseState[+button];
}

void WindowSystem::WindowsWindow::GetMousePosition(std::int32_t& x, std::int32_t& y) const
{
	x = m_inputState.MousePosX;
	y = m_inputState.MousePosY;
}

std::int32_t WindowSystem::WindowsWindow::GetMousePositionX() const
{
	return m_inputState.MousePosX;
}

std::int32_t WindowSystem::WindowsWindow::GetMousePositionY() const
{
	return m_inputState.MousePosY;
}

bool WindowSystem::WindowsWindow::ShouldClose() const
{
	return m_shouldClose;
}

void WindowSystem::WindowsWindow::Close()
{
	m_shouldClose = true;
}

bool WindowSystem::WindowsWindow::Init()
{
	HINSTANCE hInstance = GetModuleHandle(nullptr);

	if (!s_isRegister) {
		s_isRegister = RegisterWND(hInstance);

		if (!s_isRegister) {
			return false;
		}
	}

	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	GetClassInfoExW(GetModuleHandle(nullptr), L"LightWindow", &wc);

	DWORD style		= StyleToWindows(m_props);
	DWORD exStyle	= ExStyleToWindows(m_props);

	RECT rect = { 0, 0, m_props.Width, m_props.Height };
	AdjustWindowRectEx(&rect, style, FALSE, exStyle);

	m_hwnd = CreateWindowExW(
		exStyle,
		wc.lpszClassName,
		Utf8ToUtf16(m_props.Title).c_str(),
		style,
		m_props.PosX, m_props.PosY,
		rect.right - rect.left,
		rect.bottom - rect.top,
		nullptr, nullptr, hInstance, this
	);

	if (!m_hwnd) return false;
	s_windowCount++;

	SetStyle(m_props.Style);

	m_saveWindowState = m_props;
	WindowMode mode = m_props.Mode;
	m_props.Mode = WindowMode::Windowed;
	SetWindowMode(mode);

	ShowWindow(m_hwnd, SW_SHOW);
	UpdateWindow(m_hwnd);

	return true;
}

bool WindowSystem::WindowsWindow::RegisterWND(HINSTANCE& hInstance) const
{
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = WndClassStyleToWindows(m_props);
	wc.lpfnWndProc = WindowsWindow::SetupWndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = L"LightWindow";
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

	if (!RegisterClassEx(&wc)) {
		return false;
	}

	return true;
}

LRESULT WindowSystem::WindowsWindow::SetupWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_NCCREATE) {
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		WindowsWindow* const pWindow = static_cast<WindowsWindow*>(pCreate->lpCreateParams);

		pWindow->m_hwnd = hwnd;
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
		SetWindowLongPtr(hwnd, GWLP_WNDPROC,  reinterpret_cast<LONG_PTR>(WindowsWindow::RouteWndProc));

		return RouteWndProc(hwnd, msg, wParam, lParam);
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT WindowSystem::WindowsWindow::RouteWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	WindowsWindow* const pWindow = reinterpret_cast<WindowsWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

	return pWindow->MainWndProc(msg, wParam, lParam);
}

LRESULT WindowSystem::WindowsWindow::MainWndProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_CLOSE: {
		WindowSystem::Event::WindowCloseEvent event;
		m_eventCallback(event);
		return 0;
	}
	case WM_SIZE: {
		m_props.Width = LOWORD(lParam);
		m_props.Height = HIWORD(lParam);
		WindowSystem::Event::WindowResizeEvent event(m_props.Width, m_props.Height);
		m_eventCallback(event);
		return 0;
	}
	case WM_SETFOCUS: {
		WindowSystem::Event::WindowFocusEvent event;
		m_eventCallback(event);
		return 0;
	}
	case WM_KILLFOCUS: {
		WindowSystem::Event::WindowLostFocusEvent event;
		m_eventCallback(event);
		return 0;
	}
	case WM_MOVE: {
		//int xPos = (short)LOWORD(lParam);
		//int yPos = (short)HIWORD(lParam);
		RECT rect;
		GetWindowRect(m_hwnd, &rect);
		m_props.PosX = rect.left;
		m_props.PosY = rect.top;
		WindowSystem::Event::WindowMovedEvent event(m_props.PosX, m_props.PosY);
		m_eventCallback(event);
		return 0;
	}
	case WM_KEYDOWN: 
	case WM_SYSKEYDOWN: {
		WindowSystem::Input::KeypadCode keypadCode = TranslateWin32KeypadToCustom(wParam, lParam);

		m_inputState.KeypadState[+keypadCode] = true;

		int originalKeypadCode = static_cast<int>(wParam);
		WindowSystem::Event::KeyPressedEvent event(keypadCode, originalKeypadCode);
		m_eventCallback(event);
		return 0;
	}
	case WM_KEYUP: 
	case WM_SYSKEYUP: {
		WindowSystem::Input::KeypadCode keypadCode = TranslateWin32KeypadToCustom(wParam, lParam);

		m_inputState.KeypadState[+keypadCode] = false;

		int originalKeypadCode = static_cast<int>(wParam);
		WindowSystem::Event::KeyReleasedEvent event(keypadCode, originalKeypadCode);
		m_eventCallback(event);
		return 0;
	}
	case WM_MOUSEMOVE: {
		int xPos = (short)LOWORD(lParam);
		int yPos = (short)HIWORD(lParam);

		m_inputState.MousePosX = xPos;
		m_inputState.MousePosY = yPos;

		WindowSystem::Event::MouseMovedEvent event(xPos, yPos);
		m_eventCallback(event);
		return 0;
	}
	case WM_MOUSEWHEEL: {
		int yDelta = (short)HIWORD(wParam);
		m_accumulatedScroll.YOffset += static_cast<float>(yDelta) / static_cast<float>(WHEEL_DELTA);
		return 0;
	}
	case WM_MOUSEHWHEEL: {
		int xDelta = (short)HIWORD(wParam);
		m_accumulatedScroll.XOffset += static_cast<float>(xDelta) / static_cast<float>(WHEEL_DELTA);
		return 0;
	}
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_XBUTTONDOWN: {
		WindowSystem::Input::MouseCode mouseCode = TranslateWin32MouseToCustom(msg, wParam);
		int xPos = (short)LOWORD(lParam);
		int yPos = (short)HIWORD(lParam);

		m_inputState.MouseState[+mouseCode] = true;
		m_inputState.MousePosX = xPos;
		m_inputState.MousePosY = yPos;

		WindowSystem::Event::MouseButtonPressedEvent event(mouseCode, xPos, yPos);
		m_eventCallback(event);
		return 0;
	}
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MBUTTONUP:
	case WM_XBUTTONUP: {
		WindowSystem::Input::MouseCode mouseCode = TranslateWin32MouseToCustom(msg, wParam);
		int xPos = (short)LOWORD(lParam);
		int yPos = (short)HIWORD(lParam);

		m_inputState.MouseState[+mouseCode] = false;
		m_inputState.MousePosX = xPos;
		m_inputState.MousePosY = yPos;

		WindowSystem::Event::MouseButtonReleasedEvent event(mouseCode, xPos, yPos);
		m_eventCallback(event);
		return 0;
	}
	case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDBLCLK:
	case WM_MBUTTONDBLCLK:
	case WM_XBUTTONDBLCLK: {
		WindowSystem::Input::MouseCode mouseCode = TranslateWin32MouseToCustom(msg, wParam);
		int xPos = (short)LOWORD(lParam);
		int yPos = (short)HIWORD(lParam);

		m_inputState.MousePosX = xPos;
		m_inputState.MousePosY = yPos;

		WindowSystem::Event::MouseButtonDoubleClickEvent event(mouseCode, xPos, yPos);
		m_eventCallback(event);
		return 0;
	}
	case WM_CHAR: {
		std::uint16_t wc = static_cast<std::uint16_t>(wParam);

		if (wc < 32 || (wc > 126 && wc < 160)) {
			return 0;
		}

		if (wc >= 0xD800 && wc <= 0xDBFF) {
			m_highSurrogate = wc;
			return 0;
		}

		std::u16string utf16Str;

		if (m_highSurrogate != 0) {
			if (wc >= 0xDC00 && wc <= 0xDFFF) {
				utf16Str += m_highSurrogate;
				utf16Str += wc;
			}
			else {
				utf16Str += 0xFFFD;
			}
			m_highSurrogate = 0;
		}
		else {
			if (wc >= 0xDC00 && wc <= 0xDFFF) {
				utf16Str += 0xFFFD;
			}
			else {
				utf16Str += wc;
			}
		}

		std::string utf8Char = Utf16ToUtf8(utf16Str);

		WindowSystem::Event::KeyTypedEvent event(utf8Char);
		m_eventCallback(event);
		return 0;
	}
	case WM_DESTROY: {
		m_shouldClose = true;
		PostQuitMessage(0);
		return 0;
	}
	}

	return DefWindowProc(m_hwnd, msg, wParam, lParam);
}
