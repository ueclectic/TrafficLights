#pragma once
#include <future>
#include <queue>

#include "Light.h"

namespace trafficlights {
	class TrafficLights
	{
		std::queue<Light*> lights_;
		Light* activeLight_;
		std::atomic_bool stopToken_;
		std::atomic_bool pauseToken_;
		const int lightRadius_;		
		const int nLights_;
		const int maxLightRadius_ = 12;

		void buildTrafficLights();
	public:
		TrafficLights(const int lightsNumber,  const int lightRadius);
		~TrafficLights();

		bool initialize();
		void start();
		void stop();
		void pause();
	};
}

