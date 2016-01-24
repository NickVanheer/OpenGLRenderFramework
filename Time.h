#pragma once

#include <chrono>
class Time
{
public:
	Time();
	~Time();


	static long getTime();
	static double getDelta();
	static double getSecond();
	static void setDelta(double delta);
	static long SECOND;
private:
	static double delta;

};

