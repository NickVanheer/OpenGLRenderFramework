#include "Time.h"

double Time::delta;
long Time::SECOND = 10000000; //1000000000L
Time::Time()
{
}


Time::~Time()
{
}


long Time::getTime()
{
	long time = 0;
	time = std::chrono::system_clock::now().time_since_epoch().count();

	return time;
}

double Time::getDelta()
{
	return delta;
}

double Time::getSecond()
{
	return 1 / 60;
}

void Time::setDelta(double delta)
{
	Time::delta = delta;
}
