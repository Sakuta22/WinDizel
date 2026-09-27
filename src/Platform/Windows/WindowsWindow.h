#pragma once
#include <Windows.h>
#include <cstdint>
#include <string>
#include <bitset>
#include "../../../include/WindowSystem/Input/KeypadCodes.h"
#include "../../../include/WindowSystem/Input/MouseCodes.h"
#include "../../../include/WindowSystem/Core/Window.h"
#include "../../../include/WindowSystem/Core/WindowProps/WindowProps.h"

namespace WindowSystem {

class WindowsWindow : public Window {
public:
	explicit WindowsWindow(const WindowProps& props = {});
	~WindowsWindow() override;

	void SetEventCallback(const EventCallbackFn& callback) override;
	
	void PollEvents() override;

	// PROPS
	WindowProps GetProps() const override;
	void SetTitle(const std::string& title) override;
	void SetPosition(std::int32_t posX, std::int32_t posY) override;
	void SetRect(std::int32_t width, std::int32_t height) override;
	void SetStyle(WindowStyle style) override;
	void SetAlpha(std::uint8_t alpha) override;
	void SetWindowMode(WindowMode windowMode) override;
	void SetSpecStyle(WindowProps::SpecStyleOS specStyle) override;

	void Minimize() override;
	void Maximize() override;
	void Restore() override;

	void Show() override;
	void Hide() override;

	// INPUT
	bool IsKeyPressed(Input::KeypadCode key) const;
	bool IsButtonPressed(Input::MouseCode button) const;
	void GetMousePosition(std::int32_t& x, std::int32_t& y) const;
	std::int32_t GetMousePositionX() const;
	std::int32_t GetMousePositionY() const;

	bool ShouldClose() const override;

	void Close() override;

private:
	bool Init();
	bool RegisterWND(HINSTANCE& hInstance) const;
	//void ShutDown();

	static LRESULT CALLBACK SetupWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK RouteWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		   LRESULT CALLBACK MainWndProc (UINT msg, WPARAM wParam, LPARAM lParam);

private:
	WindowProps m_props;
	HWND		m_hwnd = nullptr;
	bool		m_shouldClose = false;

	inline static int  s_windowCount = 0;

	// RegisterWND
	inline static bool s_isRegister = false;

	EventCallbackFn m_eventCallback;

	// INPUT
	struct InputState {
		std::bitset<1 << 16> KeypadState = { false };
		std::bitset<1 << 8>  MouseState = { false };
		std::int32_t MousePosX = 0;
		std::int32_t MousePosY = 0;
	};
	InputState m_inputState;

	// WM_CHAR
	std::uint16_t m_highSurrogate = 0;

	// WM_MOUSEWHEEL / WM_MOUSEHWHEEL
	struct AccumulatedScroll {
		float XOffset = 0.f, YOffset = 0.f;
		void ToZero() { XOffset = YOffset = 0.f; }
		bool operator==(float offset) const { return XOffset == offset && YOffset == offset; }
		bool operator!=(float offset) const { return !((*this) == offset); }
	};
	AccumulatedScroll m_accumulatedScroll;

	// SaveWindowState For WindowMode
	struct SaveWindowState {
		std::int32_t		PosX		= CW_USEDEFAULT;
		std::int32_t		PosY		= CW_USEDEFAULT;
		std::int32_t		Width		= 500;
		std::int32_t		Height		= 500;
		WindowStyle			Style		= WindowStyle::Default;
		WindowsSpecStyle	SpecStyle	= WindowsSpecStyle::Default;

		SaveWindowState& operator=(WindowProps& props) {
			PosX		= props.PosX;
			PosY		= props.PosY;
			Width		= props.Width;
			Height		= props.Height;
			Style		= props.Style;
			SpecStyle	= props.SpecStyle.Windows;

			return *this;
		}
	};
	SaveWindowState m_saveWindowState;
};

} // ::WindowSystem