#pragma once

#include <chrono>
class Time
{
public:
	Time();
	~Time();


	static double getTime();
	static double getSecond();

	static long SECOND;
private:
	static double delta;

};

