#include "WinDizel/WinDizel.h"
#include <iostream>
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
	vector<std::uint32_t> pixels(1920*1080);
	float t = 0.f;
	window->SetEventCallback(OnEvent);
	while (!window->ShouldClose()) {
		t += 0.03f;
		int w = window->GetProps().Width, h = window->GetProps().Height;
		cout << "! " << w << " " << h << endl;
		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				std::uint8_t r = 255 * (1.f + sinf(t)) / 2.f;
				std::uint8_t g = (y * 255) / h;
				std::uint8_t b = 255 * (1.f + cosf(t)) / 2.f;
				pixels[y * w + x] = (r << 24) | (g << 16) | (b << 8);
				//pixels[y * w + x] = (255 << 24) | (0 << 16) | (0 << 8) | 0;
			}
		}

		WindowSystem::Graphics::FrameContract fc;
		fc.Height = h;
		fc.Width = w;
		fc.PixelType = WindowSystem::Graphics::PixelType::RGBA32;

		WindowSystem::Graphics::Frame frame;
		frame.Data = pixels.data();
		frame.FrameContract = fc;

		window->CNSetFrame(frame);
		window->PollEvents();
	}
}