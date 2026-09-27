#pragma once
#include <memory>
#include <functional>
#include "WindowProps/WindowProps.h"
#include "../Input/KeypadCodes.h"
#include "../Input/MouseCodes.h"

// Forward Declaration
namespace WindowSystem {
namespace Event {
class Event;
} // ::Event
} // ::WindowSystem

namespace WindowSystem {

class Window {
public:
	using EventCallbackFn = std::function<void(Event::Event&)>;

	virtual ~Window() = default;

	static std::unique_ptr<Window> Create(const WindowProps& props = {});

	virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
	
	virtual void PollEvents() = 0;

	//virtual void* GetNativeHandle() const = 0;

	// PROPS
	virtual WindowProps GetProps() const = 0;
	virtual void SetTitle(const std::string& title) = 0;
	virtual void SetPosition(std::int32_t posX, std::int32_t posY) = 0;
	virtual void SetRect(std::int32_t width, std::int32_t height) = 0;
	virtual void SetStyle(WindowStyle style) = 0;
	virtual void SetAlpha(std::uint8_t alpha) = 0;
	virtual void SetWindowMode(WindowMode windowMode) = 0;
	virtual void SetSpecStyle(WindowProps::SpecStyleOS specStyle) = 0;
	
	virtual void Minimize() = 0;
	virtual void Maximize() = 0;
	virtual void Restore() = 0;

	virtual void Show() = 0;
	virtual void Hide() = 0;

	// INPUT
	virtual bool IsKeyPressed(Input::KeypadCode key) const = 0;
	virtual bool IsButtonPressed(Input::MouseCode button) const = 0;
	virtual void GetMousePosition(std::int32_t& x, std::int32_t& y) const = 0;
	virtual std::int32_t GetMousePositionX() const = 0;
	virtual std::int32_t GetMousePositionY() const = 0;

	virtual bool ShouldClose() const = 0;

	virtual void Close() = 0;
};

} // ::WindowSystem