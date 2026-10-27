#pragma once
#include <cstdint>

namespace WindowSystem {

namespace Graphics {

enum class PixelType : std::uint8_t {
	RGBA32 = 0
};

struct FrameContract {
	std::uint32_t	Width		= 0;
	std::uint32_t	Height		= 0;

	PixelType		PixelType	= PixelType::RGBA32;
	//std::uint32_t	MaskOfRed	= 0xFF000000;
	//std::uint32_t	MaskOfGreen	= 0x00FF0000;
	//std::uint32_t	MaskOfBlue	= 0x0000FF00;
	//std::uint32_t	MaskOfAlpha	= 0x000000FF;
	std::uint32_t	MaskOfAlpha	= 0xFF000000;
	std::uint32_t	MaskOfRed	= 0x00FF0000;
	std::uint32_t	MaskOfGreen = 0x0000FF00;
	std::uint32_t	MaskOfBlue	= 0x000000FF;
};

struct Frame {
	const void*		Data = nullptr;	
	FrameContract	FrameContract;

	bool IsValid() const noexcept {
		return Data != nullptr && FrameContract.Width > 0 && FrameContract.Height > 0;
	};
};

} // ::Graphics

} // ::WindowSystem
