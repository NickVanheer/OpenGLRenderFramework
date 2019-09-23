#pragma once
#include "pch.h"
#include "Helpers.h"
#include <tchar.h>

#include <fstream>
#include <sstream>
#include <stdio.h>  

#define M_PI 3.14159265358979323846

double TO_RADIANS(float degrees)
{
	double radians = (degrees * M_PI) / 180;
	return radians;
}

double TO_DEGREES(float radians)
{
	double degrees = (radians * 180) / M_PI;
	return degrees;
}

int RandomRange(int min, int max)
{
	return rand() % (max - min) + min;
}

float RandomFloat(float min, float max)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = max - min;
	float r = random * diff;
	return min + r;
}

float RangeConverter(float oldValue, float oldMin, float oldMax, float newMin, float newMax)
{
	float new_value = ((oldValue - oldMin) / (oldMax - oldMin)) * (newMax - newMin) + newMin;
	return new_value;
}

float  sq4root(float a) { return a*a; }

std::vector<std::string> &SPLIT(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}


std::vector<std::string> SPLIT(const std::string &s, char delim) {
	std::vector<std::string> elems;
	SPLIT(s, delim, elems);
	return elems;
}
