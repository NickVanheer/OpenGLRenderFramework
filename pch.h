#pragma once

#include <iostream>
#include <functional>
#include <memory>
#include <thread>
#include <chrono>
#include <string>
#include <vector>
#include <math.h>
#include <string>

//
#include "Vector2.h"
#include "Vector3.h"
#include "Vertex.h"
#include "Matrix4.h"

#include <SDL.h>


//Object lifetime timer
struct Timer
{
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration;
	const char* m_Name;

	bool isPrintDuration = true;

	void PrintDuration()
	{
		float ms = duration.count() * 1000.0f;
		std::cout << "Timer " << "[" << m_Name << "] : " << ms << "ms (" << duration.count() << "s ) " << std::endl;
	}

	Timer() : m_Name("unnnamed")
	{
		start = std::chrono::high_resolution_clock::now();
	}

	Timer(const char* name) : m_Name(name)
	{
		start = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;

		if (isPrintDuration)
			PrintDuration();
	}
};

static std::vector<float> GetFloatVector(std::vector<Vertex> vertices);