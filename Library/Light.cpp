#pragma once
#include <iostream>
#include <string>

#include "Light.h"
#include "Graphics.h"

using namespace std;
using namespace trafficlights;


Light::Light(Color color, const int duration, const bool isBlinking, const int radius, const Point center) :
	color_(color),
	duration_(duration),
	isBlinking_(isBlinking),
	isBlinked_(false),
	radius_(radius),
	center_(center),
	stopToken_(false),
	pauseToken_(false)
{
}


Light::~Light()
{
}

bool trafficlights::Light::initialize()
{
	turnOnLight();
	const int delay = 1000;
	for (int i = duration_ * 1000; i > 0;) {
		if (stopToken_) {
			return false;
		}

		if (!pauseToken_) {
			i -= delay;
		}
		else {
			std::this_thread::sleep_for(std::chrono::milliseconds(delay));
			continue;
		}

		if (isBlinking_ && i % 1000 == 0) {
			if (isBlinked_) {
				turnOffLight();
			}
			else {
				turnOnLight();
			}
			isBlinked_ = !isBlinked_;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));

	}

	turnOffLight();

	return true;
}



void Light::start()
{
	stopToken_ = false;
	pauseToken_ = false;
}


void Light::stop()
{
	turnOffLight();
	stopToken_ = true;
}


void Light::pause()
{
	pauseToken_ = true;
}

void trafficlights::Light::show()
{
	drawLight(false);
}



bool trafficlights::Light::drawLight(const bool lightColor)
{
	int color;
	if (lightColor) {
		color = Graphics::getLightColor(color_);
		if (color == -1) {
			return false;
		}
	}
	else {
		color = static_cast<int>(color_);
	}

	return Graphics::drawCircle(center_, radius_, color);
}


void trafficlights::Light::turnOnLight()
{
	drawLight(true);
}



void trafficlights::Light::turnOffLight()
{
	pauseToken_ = false;
	stopToken_ = false;
	drawLight(false);
}



