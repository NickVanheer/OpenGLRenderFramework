#pragma once

class Time
{
public:
	Time();
	~Time();

	static long getTime();
	static long getTimeMili();
	static double getSecond();

	static long SECOND;
private:
	static double delta;

};

