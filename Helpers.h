#pragma once
#include <string.h>
#include <assert.h>
#include <iostream>
#include <vector>

float  sq4root(float a);


double TO_RADIANS(float degrees);
float RangeConverter(float oldValue, float oldMin, float oldMax, float newMin, float newMax);

double TO_DEGREES(float radians);
std::vector<std::string> &SPLIT(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> SPLIT(const std::string &s, char delim);

struct tridata {
	int	v[3];  // indices to vertex list
	int	t[3];  // indices to normal list
	int	n[3];  // indices to normal list
};

struct GameContext
{
	float deltaTime;
};


#pragma region helpers

#pragma endregion


#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#ifndef NDEBUG
#define ASSERT(condition) \
{							\
	if (!(condition))			\
	{						\
		std::cout << "Assertion failed at " << __FILE__ << ":" << __LINE__;	\
		std::cout << " inside " << __FUNCTION__ << std::endl;	\
		std::cout << "Condition: " << #condition;	\
		abort();	\
	}	\
}

#define LOGMESSAGE(msg) \
{							\
	std::cout <<  msg << " (" << __FILENAME__ << ":" << __LINE__;	\
	std::cout << ", inside " << __FUNCTION__ ;\
	std::cout << ")\n";	\
}

#define LOGERROR(msg) \
{							\
	std::cout <<  "ERROR: " msg << " (" << __FILENAME__ << ":" << __LINE__;	\
	std::cout << ", inside " << __FUNCTION__ ;\
	std::cout << ")\n--------------------\n";	\
}


#endif



