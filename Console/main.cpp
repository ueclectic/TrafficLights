#pragma once
#include <iostream>
#include <string>
#include <conio.h>

#include "Graphics.h";
#include "TrafficLights.h"

using namespace std;
using namespace trafficlights;


void sendNotification(string message);

int main() {

	bool isStopped = false;
	try {
		TrafficLights trafficLights(3, 10);
		future<bool> trafficLightsResponse = async(launch::async, &TrafficLights::initialize, &trafficLights);


		while (true)
		{
			char command;
			try {
				cin >> command;

				if (command == 'S' || command == 's')
				{
					sendNotification("Started...");
					trafficLights.start();
				}
				else if (command == 'P' || command == 'p')
				{
					sendNotification("Paused...");
					trafficLights.pause();
				}
				else if (command == 'E' || command == 'e')
				{
					sendNotification("Stopped...");
					trafficLights.stop();

					return 0;
				}
				else {
					throw exception();
				}
			}
			catch (...) {
				sendNotification("Incorrect command. Try 'S' to start, 'P' to pause, 'E' to exit");
			}
		}
		isStopped = trafficLightsResponse.get();
		sendNotification("Stopped");
	}
	catch (...) {
		sendNotification("Traffic lights are broken");
	}
	return 0;
}

void sendNotification(string message) {
	Graphics::setColor(0x0C);
	Graphics::gotoXY(0,1);
	cout << "\t\t\t\t\t\t\t\t";

	Graphics::gotoXY(0,1);
	cout << message << endl;
	Graphics::gotoXY(0, 0);
}

