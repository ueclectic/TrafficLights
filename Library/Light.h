#pragma once
#include <future>
#include <string>

#include "Color.h"
#include "Point.h"

namespace trafficlights {
	class Light
	{
		const Color color_;
		const int duration_;
		const bool isBlinking_;
		bool isBlinked_;
		const int radius_;
		const Point center_;
		std::atomic_bool stopToken_;
		std::atomic_bool pauseToken_;

		bool drawLight(const bool lightColor);
		void turnOnLight();
		void turnOffLight();
	public:
		Light(Color color, const int duration, const bool isBlinking, const int radius, const Point center);
		~Light();
		bool initialize();
		void start();
		void stop();
		void pause();
		void show();
		const char* getColor();
	};
}

