#pragma once
#include <Windows.h>

#include "WinDizel/Input/MouseCodes.h"

inline WindowSystem::Input::MouseCode TranslateWin32MouseToCustom(UINT msg, WPARAM wParam)
{
    switch (msg)
    {
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_LBUTTONDBLCLK:
        return WindowSystem::Input::Mouse::Left;

    case WM_RBUTTONDOWN:
    case WM_RBUTTONUP:
    case WM_RBUTTONDBLCLK:
        return WindowSystem::Input::Mouse::Right;

    case WM_MBUTTONDOWN:
    case WM_MBUTTONUP:
    case WM_MBUTTONDBLCLK:
        return WindowSystem::Input::Mouse::Middle;

    case WM_XBUTTONDOWN:
    case WM_XBUTTONUP:
    case WM_XBUTTONDBLCLK:
    {
        WORD xbutton = GET_XBUTTON_WPARAM(wParam);
        if (xbutton == XBUTTON1) return WindowSystem::Input::Mouse::Back;
        if (xbutton == XBUTTON2) return WindowSystem::Input::Mouse::Forward;
        break;
    }
    }

    return WindowSystem::Input::Mouse::None;
}