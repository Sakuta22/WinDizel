#pragma once
#include <Windows.h>

#include "WinDizel/Core/WindowProps/WindowProps.h"

inline DWORD StyleToWindows(const WindowSystem::WindowProps& props) {
	using namespace WindowSystem;

	WindowStyle			style		= props.Style;
	WindowsSpecStyle	specStyle	= props.SpecStyle.Windows;

	if (style == WindowStyle::None) {
		return WS_POPUP;
	}

	DWORD windowsStyle = 0;

	if (HasFlag(style, WindowStyle::Popup)) {
		windowsStyle |= WS_POPUP;
	}

	if (HasFlag(style, WindowStyle::Border)) {
		windowsStyle |= WS_BORDER;
	}

	if (HasFlag(style, WindowStyle::TitleBar)) {
		windowsStyle |= WS_CAPTION;
	}

	if (HasFlag(style, WindowStyle::Resizable)) {
		windowsStyle |= WS_THICKFRAME;
	}

	if (HasFlag(style, WindowStyle::CloseButton) ||
		HasFlag(style, WindowStyle::MinimizeButton) ||
		HasFlag(style, WindowStyle::MaximizeButton)) {
		windowsStyle |= WS_SYSMENU;
	}

	if (HasFlag(style, WindowStyle::MinimizeButton)) {
		windowsStyle |= WS_MINIMIZEBOX;
	}

	if (HasFlag(style, WindowStyle::MaximizeButton)) {
		windowsStyle |= WS_MAXIMIZEBOX;
	}

	if (HasFlag(style, WindowStyle::Visible)) {
		windowsStyle |= WS_VISIBLE;
	}

	if (windowsStyle == 0) {
		return WS_POPUP;
	}

	return windowsStyle;
}

inline DWORD ExStyleToWindows(const WindowSystem::WindowProps& props) {
	using namespace WindowSystem;

	WindowStyle			style		= props.Style;
	WindowsSpecStyle	specStyle	= props.SpecStyle.Windows;
	
	DWORD windowsExStyle = 0;

	if (HasFlag(style, WindowStyle::AlwaysOnTop)) {
		windowsExStyle |= WS_EX_TOPMOST;
	}

	if (HasFlag(style, WindowStyle::Transparent)) {
		windowsExStyle |= WS_EX_LAYERED;
	}

	if (HasFlag(style, WindowStyle::ThroughClick)) {
		windowsExStyle |= WS_EX_TRANSPARENT;
	}

	if (HasFlag(style, WindowStyle::TaskbarIcon)) {
		windowsExStyle |= WS_EX_APPWINDOW;
	}

	return windowsExStyle;
}

inline DWORD WndClassStyleToWindows(const WindowSystem::WindowProps& props) {
	using namespace WindowSystem;

	WindowStyle			style		= props.Style;
	WindowsSpecStyle	specStyle	= props.SpecStyle.Windows;

	DWORD windowsWndClassStyle = 0;

	if (HasFlag(specStyle, WindowsSpecStyle::DoubleClick)) {
		windowsWndClassStyle |= CS_DBLCLKS;
	}

	if (HasFlag(specStyle, WindowsSpecStyle::DropShadow)) {
		windowsWndClassStyle |= CS_DROPSHADOW;
	}

	if (HasFlag(specStyle, WindowsSpecStyle::NoClose)) {
		windowsWndClassStyle |= CS_NOCLOSE;
	}

	if (HasFlag(specStyle, WindowsSpecStyle::OwnDC)) {
		windowsWndClassStyle |= CS_OWNDC;
	}

	return windowsWndClassStyle;
}