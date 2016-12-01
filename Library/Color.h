#pragma once

namespace trafficlights {

	enum class Color{
		Red = 0x44, Yellow = 0x66, Green = 0x22
	};

	int getLightColor(Color color) {
		switch (color)
		{
		case Color::Red:
			return 0xCC;
		case Color::Yellow:
			return 0xEE;
		case Color::Green:
			return 0xAA;
		default:
			return -1;
		}
	}
}
