#pragma once
#include <string>
#include "Event.h"
#include "../Input/KeypadCodes.h"

namespace WindowSystem {

namespace Event {

// Type::KeyPressed
class KeyPressedEvent : public Event {
public:
	KeyPressedEvent(Input::KeypadCode keypadCode, int originalCode)
		: m_keypadCode(keypadCode), m_originalCode(originalCode) { }

	static Type GetStaticType() { return Type::KeyPressed; }
	Type GetType() const override { return GetStaticType(); }

	Input::KeypadCode GetKeyCode() const { return m_keypadCode; }
	int GetOriginalCode() const { return m_originalCode; }

private:
	Input::KeypadCode m_keypadCode;
	int m_originalCode;
};

// Type::KeyReleased
class KeyReleasedEvent : public Event {
public:
	KeyReleasedEvent(Input::KeypadCode keypadCode, int originalCode)
		: m_keypadCode(keypadCode), m_originalCode(originalCode) { }

	static Type GetStaticType() { return Type::KeyReleased; }
	Type GetType() const override { return GetStaticType(); }

	Input::KeypadCode GetKeyCode() const { return m_keypadCode; }
	int GetOriginalCode() const { return m_originalCode; }

private:
	Input::KeypadCode m_keypadCode;
	int m_originalCode;
};

// Type::KeyTyped
class KeyTypedEvent : public Event {
public:
	KeyTypedEvent(std::string keyCharacter)
		: m_keyCharacter(keyCharacter) { }

	static Type GetStaticType() { return Type::KeyTyped; }
	Type GetType() const override { return GetStaticType(); }

	std::string GetKeyCharacter() const { return m_keyCharacter; }

private:
	std::string m_keyCharacter;
};

} // ::Event

} // ::WindowSystem
