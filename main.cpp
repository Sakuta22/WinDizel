#include "WinDizel/WinDizel.h"
#include <chrono>
#include <iostream>
#include <numbers>
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
	vector < pair<float, float> > trig;
	float t = 0.f;
	do {
		trig.push_back({ sinf(t) / 2.f, cosf(t) / -2.f });
		t += 0.05f;
	} while (t <= 2 * numbers::pi);
	cout << trig.size() << endl;

	vector<std::uint32_t> pixels(1920*1080);
	int idx = 0;
	float we = 0.f;
	window->SetEventCallback(OnEvent);
	while (!window->ShouldClose()) {
		we += 0.01f;
		if (we - 0.5f >= 0.f)
			we -= 0.5f;
		idx = (idx + 1) % trig.size();
		float sinx = trig[idx].first, cosx = trig[idx].second;
		int w = window->GetProps().Width, h = window->GetProps().Height;
		float _w = 2.f / (float)w, _y = 2.f / (float)h;
		int yw = -w;
		for (int y = 0; y < h; y++) {
			float cy = _y * (float)y - 1.f + cosx;
			float cy2 = cy * cy;
			yw += w;
			for (int x = 0; x < w; x++) {
				float cx = (_w * (float)x - 1.f) * (float)w / float(h) + sinx;
				if (cx * cx + cy2 <= 0.25f) {
					pixels[yw + x] = 0xFFFFFFFF;
				}
				else {
					pixels[yw + x] = 0x00000000;
				}
				//std::uint8_t r = 255 * (1.f + sinf(t)) / 2.f;
				//std::uint8_t g = (y * 255) / h;
				//std::uint8_t b = 255 * (1.f + cosf(t)) / 2.f;
				//pixels[y * w + x] = (0 << 24) | (0 << 16) | (0 << 8);
				//pixels[y * w + x] = (255 << 24) | (0 << 16) | (0 << 8) | 0;
			}
		}
		auto start = std::chrono::steady_clock::now();

		WindowSystem::Graphics::FrameContract fc;
		fc.Height = h;
		fc.Width = w;
		fc.PixelType = WindowSystem::Graphics::PixelType::RGBA32;

		WindowSystem::Graphics::Frame frame;
		frame.Data = pixels.data();
		frame.FrameContract = fc;

		window->SetFrame(frame);
		window->PollEvents();

		auto end = std::chrono::steady_clock::now();
		std::chrono::duration<double, std::milli> elapsed = end - start;
		std::cout << "Time: " << elapsed.count() << " ms\n";
	}
}