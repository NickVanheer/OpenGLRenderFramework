#pragma once

#include <string>
#include <memory>
#include "Time.h"

class Window;

class BaseGame;
class InputManager;
class RenderEngine;

class CoreEngine
{
	
public:
	CoreEngine(int width, int height, int framerate, BaseGame* game);
	virtual ~CoreEngine();
	void start();
	void stop();
	void run();
	void cleanUp();

	void CreateWindow(const char* title);

private:
	bool m_isSingleFrame;
	Time m_Time;
	BaseGame* m_game;
	bool m_isRunning = false;
	double m_frameTime;
	int m_frameRate;
	int m_width;
	int m_height;
	RenderEngine* renderingEngine;

	std::shared_ptr<InputManager> m_inputManager;
	std::shared_ptr<Window> m_window;
};