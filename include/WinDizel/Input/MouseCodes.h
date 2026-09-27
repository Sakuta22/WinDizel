#pragma once
#include <cstdint>
#include <type_traits>

namespace WindowSystem {

namespace Input {

enum class MouseCode : std::uint8_t {
	Unknown		= 255, // -1
	None		= 0,

	Button0		= 1,
	Button1		= 2,
	Button2		= 3,
	Button3		= 4,
	Button4		= 5,
	Button5		= 6,
	Button6		= 7,
	Button7		= 8,

	Left		= Button0,
	Right		= Button1,
	Middle		= Button2,

	Back		= Button3,
	Forward		= Button4,

	Last		= Button7
};
using Mouse = MouseCode;

inline constexpr std::uint8_t operator+(MouseCode code) noexcept {
	return static_cast<std::underlying_type_t<Mouse>>(code);
}

const char* MouseCodeToString(MouseCode code);

} // ::Input

} // ::WindowSystem