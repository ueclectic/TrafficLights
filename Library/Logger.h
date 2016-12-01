#pragma once
#include <string>

class Logger
{
public:
	Logger();
	~Logger();
	static void write(std::string message);
};

