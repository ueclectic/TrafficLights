#pragma once
#include <Windows.h>

#include "Graphics.h"

using namespace trafficlights;

void Graphics::hideCursor(bool hide)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = !hide;
	SetConsoleCursorInfo(out, &cursorInfo);
}

void Graphics::gotoXY(short x, short y)
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

void Graphics::setColour(const int colour)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colour);
}

int  Graphics::getLightColor(Color color) {
	switch (color)
	{
	case Color::Red:
		return 0xCC;
	case Color::Yellow:
		return 0xEE;
	case Color::Green:
		return 0xAA;
	default:
		return -1;
	}
}