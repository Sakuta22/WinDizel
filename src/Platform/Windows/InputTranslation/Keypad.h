#pragma once
#include <Windows.h>

#include "WinDizel/Input/KeypadCodes.h"

inline WindowSystem::Input::KeypadCode TranslateWin32KeypadToCustom(WPARAM wParam, LPARAM lParam)
{
	if (wParam >= 'A' && wParam <= 'Z') {
		return static_cast<WindowSystem::Input::KeypadCode>(wParam);
	}
	if (wParam >= '0' && wParam <= '9') {
		return static_cast<WindowSystem::Input::KeypadCode>(wParam);
	}

	switch (wParam)
	{
	case VK_SHIFT: {
		UINT scancode = (lParam & 0x00ff0000) >> 16;
		return MapVirtualKey(scancode, MAPVK_VSC_TO_VK_EX) == VK_RSHIFT ? WindowSystem::Input::Keypad::RightShift : WindowSystem::Input::Keypad::LeftShift;
	}
	case VK_CONTROL: {
		return (lParam & 0x01000000) ? WindowSystem::Input::Keypad::RightControl : WindowSystem::Input::Keypad::LeftControl;
	}
	case VK_MENU: {
		return (lParam & 0x01000000) ? WindowSystem::Input::Keypad::RightAlt : WindowSystem::Input::Keypad::LeftAlt;
	}
	case VK_LWIN:		return WindowSystem::Input::Keypad::LeftSuper;
	case VK_RWIN:		return WindowSystem::Input::Keypad::RightSuper;
	case VK_APPS:		return WindowSystem::Input::Keypad::Menu;

	case VK_ESCAPE:		return WindowSystem::Input::Keypad::Escape;
	case VK_RETURN:		return WindowSystem::Input::Keypad::Enter;
	case VK_TAB:		return WindowSystem::Input::Keypad::Tab;
	case VK_BACK:		return WindowSystem::Input::Keypad::Backspace;
	case VK_INSERT:		return WindowSystem::Input::Keypad::Insert;
	case VK_DELETE:		return WindowSystem::Input::Keypad::Delete;

	case VK_RIGHT:		return WindowSystem::Input::Keypad::Right;
	case VK_LEFT:		return WindowSystem::Input::Keypad::Left;
	case VK_DOWN:		return WindowSystem::Input::Keypad::Down;
	case VK_UP:			return WindowSystem::Input::Keypad::Up;
	case VK_PRIOR:		return WindowSystem::Input::Keypad::PageUp;
	case VK_NEXT:		return WindowSystem::Input::Keypad::PageDown;
	case VK_HOME:		return WindowSystem::Input::Keypad::Home;
	case VK_END:		return WindowSystem::Input::Keypad::End;

	case VK_CAPITAL:	return WindowSystem::Input::Keypad::CapsLock;
	case VK_SCROLL:		return WindowSystem::Input::Keypad::ScrollLock;
	case VK_NUMLOCK:	return WindowSystem::Input::Keypad::NumLock;
	case VK_SNAPSHOT:	return WindowSystem::Input::Keypad::PrintScreen;
	case VK_PAUSE:		return WindowSystem::Input::Keypad::Pause;

	case VK_SPACE:		return WindowSystem::Input::Keypad::Space;
	case VK_OEM_7:		return WindowSystem::Input::Keypad::Apostrophe;   // '
	case VK_OEM_COMMA:	return WindowSystem::Input::Keypad::Comma;        // ,
	case VK_OEM_MINUS:	return WindowSystem::Input::Keypad::Minus;        // -
	case VK_OEM_PERIOD:	return WindowSystem::Input::Keypad::Period;       // .
	case VK_OEM_2:		return WindowSystem::Input::Keypad::Slash;        // /
	case VK_OEM_1:		return WindowSystem::Input::Keypad::Semicolon;    // ;
	case VK_OEM_PLUS:	return WindowSystem::Input::Keypad::Equal;        // =
	case VK_OEM_4:		return WindowSystem::Input::Keypad::LeftBracket;  // [
	case VK_OEM_5:		return WindowSystem::Input::Keypad::Backslash;    // "\"
	case VK_OEM_6:		return WindowSystem::Input::Keypad::RightBracket; // ]
	case VK_OEM_3:		return WindowSystem::Input::Keypad::GraveAccent;  // `

	case VK_F1:			return WindowSystem::Input::Keypad::F1;
	case VK_F2:			return WindowSystem::Input::Keypad::F2;
	case VK_F3:			return WindowSystem::Input::Keypad::F3;
	case VK_F4:			return WindowSystem::Input::Keypad::F4;
	case VK_F5:			return WindowSystem::Input::Keypad::F5;
	case VK_F6:			return WindowSystem::Input::Keypad::F6;
	case VK_F7:			return WindowSystem::Input::Keypad::F7;
	case VK_F8:			return WindowSystem::Input::Keypad::F8;
	case VK_F9:			return WindowSystem::Input::Keypad::F9;
	case VK_F10:		return WindowSystem::Input::Keypad::F10;
	case VK_F11:		return WindowSystem::Input::Keypad::F11;
	case VK_F12:		return WindowSystem::Input::Keypad::F12;

	case VK_NUMPAD0:	return WindowSystem::Input::Keypad::KP_0;
	case VK_NUMPAD1:	return WindowSystem::Input::Keypad::KP_1;
	case VK_NUMPAD2:	return WindowSystem::Input::Keypad::KP_2;
	case VK_NUMPAD3:	return WindowSystem::Input::Keypad::KP_3;
	case VK_NUMPAD4:	return WindowSystem::Input::Keypad::KP_4;
	case VK_NUMPAD5:	return WindowSystem::Input::Keypad::KP_5;
	case VK_NUMPAD6:	return WindowSystem::Input::Keypad::KP_6;
	case VK_NUMPAD7:	return WindowSystem::Input::Keypad::KP_7;
	case VK_NUMPAD8:	return WindowSystem::Input::Keypad::KP_8;
	case VK_NUMPAD9:	return WindowSystem::Input::Keypad::KP_9;
	case VK_DECIMAL:	return WindowSystem::Input::Keypad::KP_Decimal;
	case VK_DIVIDE:		return WindowSystem::Input::Keypad::KP_Divide;
	case VK_MULTIPLY:	return WindowSystem::Input::Keypad::KP_Multiply;
	case VK_SUBTRACT:	return WindowSystem::Input::Keypad::KP_Subtract;
	case VK_ADD:		return WindowSystem::Input::Keypad::KP_Add;

	default:            return WindowSystem::Input::Keypad::None;
	}
}