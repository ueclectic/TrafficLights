#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>

#include "Logger.h"

using namespace std;

Logger::Logger()
{
}


Logger::~Logger()
{
}

void Logger::write(std::string message)
{
	ofstream myfile("log.txt", ios_base::out | ios_base::app);
	if (myfile.is_open())
	{
		auto t = std::time(nullptr);
		auto tm = *std::localtime(&t);

		myfile <<"["<< std::put_time(&tm, "%d-%m-%Y %H-%M-%S")<<"] "<< message << "\n";
		myfile.close();
	}
}
