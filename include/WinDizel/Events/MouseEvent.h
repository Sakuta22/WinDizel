#pragma once
#include "Event.h"
#include "../Input/MouseCodes.h"

namespace WindowSystem {

namespace Event {

// Type::MouseMoved
class MouseMovedEvent : public Event {
public:
	MouseMovedEvent(int x, int y)
		: m_x(x), m_y(y) {
	}

	static Type GetStaticType() { return Type::MouseMoved; }
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

// Type::MouseScrolled
class MouseScrolledEvent : public Event {
public:
	MouseScrolledEvent(float xOffset, float yOffset)
		: m_xOffset(xOffset), m_yOffset(yOffset) {
	}

	static Type GetStaticType() { return Type::MouseScrolled; }
	Type GetType() const override { return GetStaticType(); }

	void GetOffset(float& xOffset, float& yOffset) const {
		xOffset = m_xOffset;
		yOffset = m_yOffset;
	}
	float GetXOffset() const { return m_xOffset; }
	float GetYOffset() const { return m_yOffset; }

private:
	float m_xOffset, m_yOffset;
};

// Type::MouseButtonPressed
class MouseButtonPressedEvent : public Event {
public:
	MouseButtonPressedEvent(Input::MouseCode mouseCode, int x, int y)
		: m_mouseCode(mouseCode), m_x(x), m_y(y) {
	}

	static Type GetStaticType() { return Type::MouseButtonPressed; }
	Type GetType() const override { return GetStaticType(); }

	Input::MouseCode GetMouseCode() const { return m_mouseCode; }
	void GetPosition(int& x, int& y) const {
		x = m_x;
		y = m_y;
	}
	int GetX() const { return m_x; }
	int GetY() const { return m_y; }

private:
	Input::MouseCode m_mouseCode;
	int m_x, m_y;
};

// Type::MouseButtonReleased
class MouseButtonReleasedEvent : public Event {
public:
	MouseButtonReleasedEvent(Input::MouseCode mouseCode, int x, int y)
		: m_mouseCode(mouseCode), m_x(x), m_y(y) {
	}

	static Type GetStaticType() { return Type::MouseButtonReleased; }
	Type GetType() const override { return GetStaticType(); }

	Input::MouseCode GetMouseCode() const { return m_mouseCode; }
	void GetPosition(int& x, int& y) const {
		x = m_x;
		y = m_y;
	}
	int GetX() const { return m_x; }
	int GetY() const { return m_y; }

private:
	Input::MouseCode m_mouseCode;
	int m_x, m_y;
};

// Type::MouseButtonDoubleClick
class MouseButtonDoubleClickEvent : public Event {
public:
	MouseButtonDoubleClickEvent(Input::MouseCode mouseCode, int x, int y)
		: m_mouseCode(mouseCode), m_x(x), m_y(y) {
	}

	static Type GetStaticType() { return Type::MouseButtonDoubleClick; }
	Type GetType() const override { return GetStaticType(); }

	Input::MouseCode GetMouseCode() const { return m_mouseCode; }
	void GetPosition(int& x, int& y) const {
		x = m_x;
		y = m_y;
	}
	int GetX() const { return m_x; }
	int GetY() const { return m_y; }

private:
	Input::MouseCode m_mouseCode;
	int m_x, m_y;
};

} // ::Event

} // ::WindowSystem
