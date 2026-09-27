#include "WinDizel/Input/MouseCodes.h"

const char* WindowSystem::Input::MouseCodeToString(MouseCode mouseCode)
{
	#define KEY_CASE(x) case WindowSystem::Input::Mouse::x: return #x;

	switch (mouseCode)
	{
	KEY_CASE(None)
	KEY_CASE(Unknown)

	case WindowSystem::Input::Mouse::Button0: return "Button0|Left";
	case WindowSystem::Input::Mouse::Button1: return "Button1|Right";
	case WindowSystem::Input::Mouse::Button2: return "Button2|Middle";
	
	case WindowSystem::Input::Mouse::Button3: return "Button3|Back";
	case WindowSystem::Input::Mouse::Button4: return "Button4|Forward";
		
	KEY_CASE(Button5)
	KEY_CASE(Button6)

	case WindowSystem::Input::Mouse::Button7: return "Button7|Last";

	default: return "InvalidMouseCode";
	}

	#undef KEY_CASE
}
