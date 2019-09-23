#include "pch.h"
#include "Time.h"

long Time::SECOND = 10000000; //1000000000L

Time::Time()
{
}


Time::~Time()
{
}


long Time::getTime()
{
	return std::chrono::system_clock::now().time_since_epoch().count();
}

long Time::getTimeMili()
{
	unsigned long milliseconds_since_epoch = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
	return milliseconds_since_epoch;
}


double Time::getSecond()
{
	return 1 / 60;
}

