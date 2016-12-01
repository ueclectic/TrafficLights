#pragma once
#include <iostream>
#include <Windows.h>
#include <math.h>

#include "Graphics.h"

using namespace trafficlights;

void Graphics::hideCursor(const bool hide)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = !hide;
	SetConsoleCursorInfo(out, &cursorInfo);
}

void Graphics::gotoXY(const short x, const short y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int Graphics::currentX()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return -1;
	return csbi.dwCursorPosition.X;
}

int Graphics::currentY()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return -1;
	return csbi.dwCursorPosition.Y;
}

void Graphics::setColor(const int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int  Graphics::getLightColor(Color color) {
	switch (color)
	{
	case (Color::Red):
		return 0xCC;
	case (Color::Yellow):
		return 0xEE;
	case (Color::Green):
		return 0xAA;
	default:
		return -1;
	}
}

bool trafficlights::Graphics::drawCircle(const Point center, const int radius, const int color)
{
	const int startX = center.X - radius;
	const int endX = center.X + radius;

	const int  startY = center.Y - radius;
	const int endY = center.Y + radius;

	//todo: check boundaries

	double r = radius;
	if ((startX+endX) % 2 == 0)
		r -= 0.5;

	for (int x = startX; x < endX; x++) {
		for (int y = startY; y < endY; y++) {

			double currentRadius = sqrt(pow((x-startX - radius),2) +pow((y-startY - radius),2));
			gotoXY(x, y);
			if (currentRadius <= r) {
				setColor(static_cast<int>(color));
				std::cout << "0";
			}
		}
	}
	gotoXY(0, 0);

	return true;
}
