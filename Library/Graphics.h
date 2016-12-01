#pragma once
#include "Color.h"

namespace trafficlights {

	class Graphics {
	public:
		static void hideCursor(bool hide);
		static void gotoXY(short x, short y);
		static int currentX();
		static int currentY();
		static void setColour(const int colour);
		static int getLightColor(Color color);
	};
}
