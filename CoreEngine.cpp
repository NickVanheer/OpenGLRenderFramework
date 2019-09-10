#include "Core.h"
#include "CoreEngine.h"
#include "Window.h"
#include "Time.h"
#include "BaseGame.h"
#include "InputManager.h"
#include <iostream>
#include "RenderEngine.h"
#include <thread>
#include <chrono> 

void CoreEngine::CreateWindow(string title)
{
	//TODO string to TCHAR
	window->CreateWindow(width, height, "OpenGL Renderer");
	this->renderingEngine = new RenderEngine();
	this->game->SetMainCamera(this->renderingEngine->GetMainCamera());
	this->renderingEngine->SetMainWindow(window);
	//TODO set game main camera

}

void CoreEngine::run()
{
	isRunning = true;
	game->Initialize();

	//
	double lastTime = time->getTime();
	double lastDrawTime = 0;
	double unprocessedTime = frameTime;
	int frames = 0;
	double frameCounter = 0;
	bool drawnFirstFrame = false;

	GameContext gameContext = GameContext();
	gameContext.renderEngine = renderingEngine;

	float timeCache = 0;
	while (isRunning)
	{
		if (window->IsCloseRequested())
			stop();

		double frameDelta = time->getTime() - lastTime; //time between the last 2 frames
		lastTime = time->getTime();

		timeCache += frameDelta;

		if (timeCache > 0.01666f)
		{
			double drawDelta = 0.016666f;
			//
			gameContext.deltaTime = drawDelta;
			game->Input(gameContext);
			game->Update(gameContext);
			//cout << frameDelta << endl;
			renderingEngine->Render(game->GetRoot(), gameContext);
			drawnFirstFrame = true;

			timeCache = 0;
		}

		window->Render();
	}
}

CoreEngine::CoreEngine(int width, int height, int framerate, BaseGame* game) : isSingleFrame(false)
{
	inputManager = std::make_shared<InputManager>();

	window = std::make_shared<Window>();
	window->SetInputManager(inputManager);

	this->time = new Time();
	this->game = game;
	this->width = width;
	this->height = height;
	this->frameRate = framerate;
	this->frameTime = 1.0 / framerate;

	isRunning = false;
}

CoreEngine::~CoreEngine()
{
	cleanUp();
}

void CoreEngine::stop()
{
	if (!isRunning)
		return;

	isRunning = false;
}

void CoreEngine::cleanUp()
{
	delete game;
	window->Close();
}

void CoreEngine::start()
{
	if (isRunning)
		return;

	//game only kicks in once the graphics stuff has been loaded.
	game->SetInputManager(inputManager);

	//start game loop
	run();
}

