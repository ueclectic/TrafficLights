#pragma once

namespace trafficlights {

	class Point {
	public:
		int X;
		int Y;
		Point(const int x, const int y) {
			X = x;
			Y = y;
		}
	};
}