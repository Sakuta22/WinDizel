#include "Platform/Windows/WindowsWindow.h"

std::unique_ptr<WindowSystem::Window> WindowSystem::Window::Create(const WindowSystem::WindowProps& props)
{
	return std::make_unique<WindowsWindow>(props);
}