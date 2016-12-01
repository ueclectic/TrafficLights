#include "TrafficLights.h"
#include <iostream>

using namespace std;
using namespace trafficlights;


TrafficLights::TrafficLights(const int lightsNumber, const int lightRadius) :
	nLights_(lightsNumber),
	lightRadius_(lightRadius),
	stopToken_(false),
	pauseToken_(false)
{
	if (lightsNumber > 3 || lightsNumber<2) {
		throw exception("Incorrect number of lights");
	}


	if (lightRadius > maxLightRadius_) {
		throw exception("Lights is too large");
	}

	buildTrafficLight();
}

void trafficlights::TrafficLights::buildTrafficLight()
{
	const int leftMargin = 10;
	const int y = 1 + lightRadius_;
	int x = lightRadius_ + leftMargin;



	activeLight_= new Light(Color::Red, 2,false, lightRadius_, Point(x, y));
	activeLight_->show();
	lights_.push(activeLight_);

	if (nLights_ == 3) {
		x += x;
		activeLight_ = new Light(Color::Yellow, 4, true, lightRadius_, Point(x, y));
		activeLight_->show();
		lights_.push(activeLight_);
	}

	x += lightRadius_ + leftMargin;
	activeLight_ = new Light(Color::Green, 3, false, lightRadius_, Point(x, y));
	activeLight_->show();
	lights_.push(activeLight_);
}


TrafficLights::~TrafficLights()
{
	while (!lights_.empty()) {
		delete lights_.front();
		lights_.pop();
	}
}


bool TrafficLights::start()
{
	while (true) {
		if (stopToken_) {
			return false;
		}

		activeLight_ = lights_.front();
		lights_.pop();
		lights_.push(activeLight_);
		future<bool> response = async(launch::async, &Light::start, activeLight_);
		response.get();

		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}

	return true;
}


void TrafficLights::stop()
{
	activeLight_->stop();
	stopToken_ = true;
}


void TrafficLights::pause()
{
	activeLight_->pause();
}



