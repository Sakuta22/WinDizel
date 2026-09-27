#pragma once
#include <type_traits>
#include <cstdint>

#define ENABLE_BITMASK_OPERATORS(Enum) \
inline constexpr Enum operator|(Enum a, Enum b) noexcept { \
    using U = std::underlying_type_t<Enum>; \
    return static_cast<Enum>(static_cast<U>(a) | static_cast<U>(b)); \
} \
inline constexpr Enum operator&(Enum a, Enum b) noexcept { \
    using U = std::underlying_type_t<Enum>; \
    return static_cast<Enum>(static_cast<U>(a) & static_cast<U>(b)); \
} \
inline constexpr Enum operator^(Enum a, Enum b) noexcept { \
    using U = std::underlying_type_t<Enum>; \
    return static_cast<Enum>(static_cast<U>(a) ^ static_cast<U>(b)); \
} \
inline constexpr Enum operator~(Enum a) noexcept { \
    using U = std::underlying_type_t<Enum>; \
    return static_cast<Enum>(~static_cast<U>(a)); \
} \
inline constexpr Enum& operator|=(Enum& a, Enum b) noexcept { \
    return a = a | b; \
} \
inline constexpr Enum& operator&=(Enum& a, Enum b) noexcept { \
    return a = a & b; \
} \
inline constexpr Enum& operator^=(Enum& a, Enum b) noexcept { \
    return a = a ^ b; \
} \
inline constexpr bool HasFlag(Enum mask, Enum flag) noexcept { \
    using U = std::underlying_type_t<Enum>; \
    return static_cast<U>(mask & flag) != static_cast<U>(0); \
} \
inline constexpr Enum& Enable(Enum& mask, Enum flag) noexcept { \
    return mask |= flag; \
} \
inline constexpr Enum& Disable(Enum& mask, Enum flag) noexcept { \
    return mask &= ~flag; \
} \
inline constexpr Enum& Toggle(Enum& mask, Enum flag) noexcept { \
    return mask ^= flag; \
}

namespace WindowSystem {

	enum class WindowStyle : std::uint32_t {
		None				= 0,

		TitleBar		= 1 << 0,
		Resizable		= 1 << 1,
		MinimizeButton	= 1 << 2,
		MaximizeButton	= 1 << 3,
		CloseButton		= 1 << 4,
		Border			= 1 << 5,
		Visible			= 1 << 6,

		AlwaysOnTop		= 1 << 7,
		Transparent		= 1 << 8,
		ThroughClick	= 1 << 9,
		TaskbarIcon		= 1 << 10,
		Focused			= 1 << 11,
		Popup			= 1 << 12,

		Borderless		= None,
		Unframed		= Border,
		FixedSize		= TitleBar | CloseButton | MinimizeButton | Border | TaskbarIcon,
		Standard		= TitleBar | Resizable | MinimizeButton | MaximizeButton | CloseButton | Border | TaskbarIcon | Visible,
		Default			= Standard
	};
	ENABLE_BITMASK_OPERATORS(WindowStyle);

	enum class WindowMode : std::uint8_t {
		Windowed = 0,
		BorderlessFullscreen = 1,
		ExclusiveFullscreen = 2
	};

	// SPECSTYLE

	enum class WindowsSpecStyle : std::uint8_t {
		None		= 0,
		DoubleClick = 1 << 0,
		DropShadow	= 1 << 1,
		NoClose		= 1 << 2,
		OwnDC		= 1 << 3,

		Default		= DoubleClick | OwnDC
	};
	ENABLE_BITMASK_OPERATORS(WindowsSpecStyle);

	//enum class LinuxSpecStyle : std::uint8_t { };
	//ENABLE_BITMASK_OPERATORS(LinuxSpecStyle);

	//enum class MacSpecStyle : std::uint8_t { };
	//ENABLE_BITMASK_OPERATORS(MacSpecStyle);

} // ::WindowSystem

#undef ENABLE_BITMASK_OPERATORS