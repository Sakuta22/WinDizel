#pragma once

namespace WindowSystem {
	
namespace Event {
	
// EventTypes
enum class Type {
	None = 0,

	// KeyEvents
	KeyPressed,
	KeyReleased,
	KeyTyped,

	// MouseEvcents
	MouseMoved,
	MouseScrolled,
	MouseButtonPressed,
	MouseButtonReleased,
	MouseButtonDoubleClick,

	// WindowEvents
	WindowClose,
	WindowResize,
	WindowFocus,
	WindowLostFocus,
	WindowMoved
};

// Event
class Event {
public:
	Event() : m_handled(false) { }

	virtual Type GetType() const = 0;

	bool IsHandled() const { return m_handled; }
	void Handle() { m_handled = true; }

	virtual ~Event() = default;

private:
	bool m_handled;
};

// EventDispatcher
class EventDispatcher {
public:
	EventDispatcher(Event& event) : m_Event(event) { }

	template<typename T, typename F>
	bool Dispatch(const F& func) {
		if (m_Event.IsHandled()) {
			return false;
		}

		if (m_Event.GetType() == T::GetStaticType()) {
			if (func(static_cast<T&>(m_Event))) {
				m_Event.Handle();	
			}
			return true;
		}
		return false;
	}

private:
	Event& m_Event;
};

} // ::Event

} // ::WindowSystem