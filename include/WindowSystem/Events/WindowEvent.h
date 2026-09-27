#pragma once
#include "Event.h"

namespace WindowSystem {

namespace Event {

// Type::WindowClose
class WindowCloseEvent : public Event {
public:
	WindowCloseEvent() = default;

	static Type GetStaticType() { return Type::WindowClose; }
	Type GetType() const override { return GetStaticType(); }
};

// Type::WindowResize
class WindowResizeEvent : public Event {
public:
	WindowResizeEvent(int width, int height)
		: m_width(width), m_height(height) { }

	static Type GetStaticType() { return Type::WindowResize; }
	Type GetType() const override { return GetStaticType(); }

	void GetSize(int& width, int& height) const {
		width = m_width;
		height = m_height;
	}
	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }

private:
	int m_width, m_height;
};

// Type::WindowFocus
class WindowFocusEvent : public Event {
public:
	WindowFocusEvent() = default;

	static Type GetStaticType() { return Type::WindowFocus; }
	Type GetType() const override { return GetStaticType(); }
};

// Type::WindowLostFocus
class WindowLostFocusEvent : public Event {
public:
	WindowLostFocusEvent() = default;

	static Type GetStaticType() { return Type::WindowLostFocus; }
	Type GetType() const override { return GetStaticType(); }
};

// Type::WindowMoved
class WindowMovedEvent : public Event {
public:
	WindowMovedEvent(int x, int y)
		: m_x(x), m_y(y) {
	}

	static Type GetStaticType() { return Type::WindowMoved; }
	Type GetType() const override { return GetStaticType(); }

	void GetPosition(int& x, int& y) const {
		x = m_x;
		y = m_y;
	}
	int GetX() const { return m_x; }
	int GetY() const { return m_y; }

private:
	int m_x, m_y;
};

} // ::Event

} // ::WindowSystem