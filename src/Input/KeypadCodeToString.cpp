#include "../../include/WindowSystem/Input/KeypadCodes.h"

const char* WindowSystem::Input::KeypadCodeToString(KeypadCode keypadCode)
{
	#define KEY_CASE(x) case WindowSystem::Input::Keypad::x: return #x;

	switch (keypadCode)
	{
	KEY_CASE(None)
	KEY_CASE(Unknown)

	KEY_CASE(A) KEY_CASE(B) KEY_CASE(C) KEY_CASE(D) KEY_CASE(E) KEY_CASE(F)
	KEY_CASE(G) KEY_CASE(H) KEY_CASE(I) KEY_CASE(J) KEY_CASE(K) KEY_CASE(L)
	KEY_CASE(M) KEY_CASE(N) KEY_CASE(O) KEY_CASE(P) KEY_CASE(Q) KEY_CASE(R)
	KEY_CASE(S) KEY_CASE(T) KEY_CASE(U) KEY_CASE(V) KEY_CASE(W) KEY_CASE(X)
	KEY_CASE(Y) KEY_CASE(Z)

	KEY_CASE(D0) KEY_CASE(D1) KEY_CASE(D2) KEY_CASE(D3) KEY_CASE(D4)
	KEY_CASE(D5) KEY_CASE(D6) KEY_CASE(D7) KEY_CASE(D8) KEY_CASE(D9)

	KEY_CASE(Space)
	KEY_CASE(Apostrophe)
	KEY_CASE(Comma)
	KEY_CASE(Minus)
	KEY_CASE(Period)
	KEY_CASE(Slash)
	KEY_CASE(Semicolon)
	KEY_CASE(Equal)
	KEY_CASE(LeftBracket)
	KEY_CASE(Backslash)
	KEY_CASE(RightBracket)
	KEY_CASE(GraveAccent)

	KEY_CASE(Escape)
	KEY_CASE(Enter)
	KEY_CASE(Tab)
	KEY_CASE(Backspace)
	KEY_CASE(Insert)
	KEY_CASE(Delete)

	KEY_CASE(Right)
	KEY_CASE(Left)
	KEY_CASE(Down)
	KEY_CASE(Up)
	KEY_CASE(PageUp)
	KEY_CASE(PageDown)
	KEY_CASE(Home)
	KEY_CASE(End)

	KEY_CASE(CapsLock)
	KEY_CASE(ScrollLock)
	KEY_CASE(NumLock)
	KEY_CASE(PrintScreen)
	KEY_CASE(Pause)

	KEY_CASE(F1) KEY_CASE(F2) KEY_CASE(F3) KEY_CASE(F4) KEY_CASE(F5) KEY_CASE(F6)
	KEY_CASE(F7) KEY_CASE(F8) KEY_CASE(F9) KEY_CASE(F10) KEY_CASE(F11) KEY_CASE(F12)

	KEY_CASE(KP_0) KEY_CASE(KP_1) KEY_CASE(KP_2) KEY_CASE(KP_3) KEY_CASE(KP_4)
	KEY_CASE(KP_5) KEY_CASE(KP_6) KEY_CASE(KP_7) KEY_CASE(KP_8) KEY_CASE(KP_9)
	KEY_CASE(KP_Decimal)
	KEY_CASE(KP_Divide)
	KEY_CASE(KP_Multiply)
	KEY_CASE(KP_Subtract)
	KEY_CASE(KP_Add)
	KEY_CASE(KP_Enter)
	KEY_CASE(KP_Equal)

	KEY_CASE(LeftShift)
	KEY_CASE(LeftControl)
	KEY_CASE(LeftAlt)
	KEY_CASE(LeftSuper)
	KEY_CASE(RightShift)
	KEY_CASE(RightControl)
	KEY_CASE(RightAlt)
	KEY_CASE(RightSuper)
	KEY_CASE(Menu)

	default: return "InvalidKeypadCode";
	}

	#undef KEY_CASE
}
