#include <string>

#pragma once
class Window;
class Time;
class Game;
class InputManager;
class RenderEngine;

class CoreEngine
{
	
public:
	CoreEngine(int width, int height, int framerate, Game* game);
	virtual ~CoreEngine();
	void start();
	void stop();
	void render();
	void run();
	void cleanUp();

	void CreateWindow(std::string title);
	void InitializeRenderingSystem();

	InputManager* inputManager;
	Window* window;
	Time* time;
	Game* game;
	bool isRunning = false;
	double frameTime;
	int width;
	int height;
	RenderEngine* renderingEngine;

	//const static double FRAME_CAP;
	//static const int WIDTH = 1280;
	//static const int HEIGHT = 720;


};