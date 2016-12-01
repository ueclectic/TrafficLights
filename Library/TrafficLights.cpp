#include <iostream>

#include "TrafficLights.h"
#include "Logger.h"

using namespace std;
using namespace trafficlights;


TrafficLights::TrafficLights(const int lightsNumber, const int lightRadius) :
	nLights_(lightsNumber),
	lightRadius_(lightRadius),
	stopToken_(false),
	pauseToken_(false)
{
	if (lightsNumber > 3 || lightsNumber < 2) {
		throw exception("Incorrect number of lights");
	}


	if (lightRadius > maxLightRadius_) {
		throw exception("Lights is too large");
	}

	buildTrafficLights();
}


void trafficlights::TrafficLights::buildTrafficLights()
{
	const int leftMargin = 10;
	const int y = 1 + lightRadius_;
	int x = lightRadius_ + leftMargin;

	activeLight_ = new Light(Color::Red, 2, false, lightRadius_, Point(x, y));
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


bool trafficlights::TrafficLights::initialize()
{
	Logger::write("Started");
	while (true) {
		if (stopToken_) {
			Logger::write("Stoped");
			return false;
		}

		if (pauseToken_) {
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			continue;
		}

		activeLight_ = lights_.front();
		lights_.pop();
		lights_.push(activeLight_);

		string message = "Turn on the light ";
		message+=activeLight_->getColor();

		Logger::write(message);
		future<bool> response = async(launch::async, &Light::initialize, activeLight_);
		response.get();

		message = "Turn off the light ";
		message += activeLight_->getColor();
		Logger::write(message);
	}

	Logger::write("Stopeed");
	return true;
}

void TrafficLights::start()
{
	stopToken_ = false;
	pauseToken_ = false;

	Logger::write("Starting...");
	activeLight_->start();
}


void TrafficLights::stop()
{
	stopToken_ = true;

	Logger::write("Stopping...");
	activeLight_->stop();
}


void TrafficLights::pause()
{
	pauseToken_ = true;

	Logger::write("Pause");
	activeLight_->pause();

}


