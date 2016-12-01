#pragma once
#include "Color.h"
#include "Point.h"

namespace trafficlights {

	class Graphics {
	public:
		static void hideCursor(const bool hide);
		static void gotoXY(const short x, const short y);
		static int currentX();
		static int currentY();
		static void setColor(const int colour);
		static int getLightColor(Color color);
		static bool drawCircle(const Point center, const int radius, const int color);
	};
}
