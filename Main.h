#pragma once
class Window;
class Time;
class Game;
class InputManager;

class Main
{
	
public:
	Main();
	virtual ~Main();
	void start();
	void stop();
	void render();
	void run();
	void cleanUp();

	InputManager* inputManager;
	Window* window;
	Time* time;
	Game* game;
	bool isRunning = false;

	const static double FRAME_CAP;
	static const int WIDTH = 1280;
	static const int HEIGHT = 720;


};