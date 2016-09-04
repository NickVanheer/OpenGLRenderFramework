#include "Time.h"

double Time::delta;
long Time::SECOND = 10000000; //1000000000L
//1000000000L
Time::Time()
{
}


Time::~Time()
{
}


double Time::getTime()
{
	long time = 0;
	time = std::chrono::system_clock::now().time_since_epoch().count();

	return (double)time / SECOND;
}


double Time::getSecond()
{
	return 1 / 60;
}

