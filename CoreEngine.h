#include <string>
#include <memory>

#pragma once
class Window;
class Time;
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

	void CreateWindow(std::string title);

private:
	bool isSingleFrame;
	std::shared_ptr<InputManager> inputManager;
	std::shared_ptr<Window> window;
	Time* time;
	BaseGame* game;
	bool isRunning = false;
	double frameTime;
	int frameRate;
	int width;
	int height;
	RenderEngine* renderingEngine;
};