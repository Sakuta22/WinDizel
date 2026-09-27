#include "include/WindowSystem/WindowSystem.h"
using namespace std;

auto window = WindowSystem::Window::Create();

bool WindowClose(WindowSystem::Event::WindowCloseEvent& event) {
	window->Close();
	return true;
}

void OnEvent(WindowSystem::Event::Event& event) {
	WindowSystem::Event::EventDispatcher dispatcher(event);

	dispatcher.Dispatch<WindowSystem::Event::WindowCloseEvent>(WindowClose);
}

int main() {
	window->SetEventCallback(OnEvent);
	while (!window->ShouldClose()) {
		window->PollEvents();
	}
}