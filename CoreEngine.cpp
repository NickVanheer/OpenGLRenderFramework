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
	
	double lastTime = time->getTime();
	double unprocessedTime = 0;
	int frames = 0;
	double frameCounter = 0;

	GameContext gameContext = GameContext();
	gameContext.deltaTime = (float)frameTime;

	while (isRunning)
	{
		double startTime = time->getTime();
		double frameDelta = startTime - lastTime; //time between the last 2 frames

		unprocessedTime += frameDelta;
		frameCounter += frameDelta;
		
		//print fps every second
		if (frameCounter >= 1.0)
		{
			printf("fps: %i \n", frames);
			frames = 0;
			frameCounter = 0;
		}

		while (unprocessedTime > frameTime)
		{
			if (window->IsCloseRequested())
				stop();

			gameContext.deltaTime = frameDelta;
			
			game->Input(gameContext);
			game->Update(gameContext);

			unprocessedTime -= frameTime;

			renderingEngine->Render(game->GetRoot(), gameContext);
			window->Render();

			frames++;

			if (isSingleFrame)
			{
				cin.get(); //wait for a keypress
				isRunning = false;
			}

			lastTime = startTime;
		}

	}
}

CoreEngine::CoreEngine(int width, int height, int framerate, BaseGame* game) : isSingleFrame(false)
{
	inputManager = new InputManager();

	window = new Window();
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

