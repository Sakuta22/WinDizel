#include "Utf.h"

std::string Utf16ToUtf8(const std::u16string& utf16) {
	std::string utf8;
	utf8.reserve(utf16.size());

	for (size_t i = 0; i < utf16.size(); ++i) {
		std::uint32_t cp = utf16[i];

		if (cp >= 0xD800 && cp <= 0xDBFF) {
			if (i + 1 < utf16.size()) {
				std::uint32_t next = utf16[i + 1];
				if (next >= 0xDC00 && next <= 0xDFFF) {
					cp = (((cp & 0x3FF) << 10) | (next & 0x3FF)) + 0x10000;
					++i;
				}
				else {
					cp = 0xFFFD;
				}
			}
			else {
				cp = 0xFFFD;
			}
		}
		else if (cp >= 0xDC00 && cp <= 0xDFFF) {
			cp = 0xFFFD;
		}

		if (cp <= 0x7F) {
			utf8 += static_cast<char>(cp);
		}
		else if (cp <= 0x7FF) {
			utf8 += static_cast<char>((cp >> 6) | 0xC0);
			utf8 += static_cast<char>((cp & 0x3F) | 0x80);
		}
		else if (cp <= 0xFFFF) {
			utf8 += static_cast<char>((cp >> 12) | 0xE0);
			utf8 += static_cast<char>(((cp >> 6) & 0x3F) | 0x80);
			utf8 += static_cast<char>((cp & 0x3F) | 0x80);
		}
		else if (cp <= 0x10FFFF) {
			utf8 += static_cast<char>((cp >> 18) | 0xF0);
			utf8 += static_cast<char>(((cp >> 12) & 0x3F) | 0x80);
			utf8 += static_cast<char>(((cp >> 6) & 0x3F) | 0x80);
			utf8 += static_cast<char>((cp & 0x3F) | 0x80);
		}
	}

	return utf8;
}