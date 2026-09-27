#pragma once
#include <string>
#include "WindowPropsEnums.h"

namespace WindowSystem {

struct WindowProps {
	std::string  Title	= "App";
	std::int32_t PosX	= static_cast<std::int32_t>(0x80000000); // CW_USEDEFAULT
	std::int32_t PosY	= static_cast<std::int32_t>(0x80000000); // CW_USEDEFAULT
	std::int32_t Width	= 500;
	std::int32_t Height	= 500;

	WindowStyle  Style	= WindowStyle::Default;
	std::uint8_t Alpha	= 255;
	WindowMode   Mode	= WindowMode::Windowed;

	struct SpecStyleOS {
		WindowsSpecStyle	Windows = WindowsSpecStyle::Default;
		//LinuxSpecStyle		Linux;
		//MacSpecStyle		Mac;
	};
	SpecStyleOS SpecStyle;
};

} // ::WindowSystem