#include "Core.h"
#include "CoreEngine.h"
#include "Window.h"
#include "Time.h"
#include "Game.h"
#include "InputManager.h"
#include <iostream>
#include "RenderEngine.h"


//const double CoreEngine::FRAME_CAP =  5000.0;
void CoreEngine::stop()
{
	if (!isRunning)
		return;

	isRunning = false;
}

void CoreEngine::cleanUp()
{
	game->Cleanup();
	window->Close();
}

void CoreEngine::render()
{
	RenderUtil::ClearScreen();

	renderingEngine->Render(game->GetRoot());
	window->Render();

	//game->Render();
	//window->Render();
}

void CoreEngine::InitializeRenderingSystem()
{
	//initialize graphics //rendercontext gets created
	std::cout << RenderUtil::GetOpenGLVersion();
	RenderUtil::InitGraphics();

	renderingEngine->Initialize();
}

void CoreEngine::CreateWindow(string title)
{
	//TODO string to TCHAR
	window->CreateWindow(width, height, "OpenGL Renderer");
	InitializeRenderingSystem();


}

void CoreEngine::run()
{
	isRunning = true;
	int frames = 0;
	long frameCounter = 0;
	
	long lastTime = time->getTime();
	double unprocessedTime = 0;
	
	
	while (isRunning)
	{
		bool doRender = false;
		long startTime = time->getTime();
		long passedTime = startTime - lastTime; //time between the last 2 frames
		lastTime = startTime;

		unprocessedTime += passedTime / (double)Time::SECOND;
		frameCounter += passedTime;
		int cc = 0;
		while (unprocessedTime > frameTime)
		{
			doRender = true;
			unprocessedTime -= frameTime;

			if (window->IsCloseRequested())
				stop();

			time->setDelta(frameTime);

			//if (inputManager->IsKeyDown(SDL_SCANCODE_UP))

			
			//TODO: Update Game
			game->Input();
			game->Update();

			if (frameCounter >= Time::SECOND)
			{
				//std::cout << frames << "\n";
				frames = 0;
				frameCounter = 0;
			}
		}
		//render
		if (doRender)
		{
			//TODO FIX 
			//renderingEngine->Render(game->GetRoot());
			//window->Render();

			render();
			frames++;
		}
		else
		{
			//thread.sleep(1); //less wasting
		}
	
	}
}

CoreEngine::CoreEngine(int width, int height, int framerate, Game* game)
{
	inputManager = new InputManager();

	window = new Window();
	window->SetInputManager(inputManager);

	//RenderUtil->InitGraphics() commented out
	this->time = new Time();
	this->game = game;
	this->width = width;
	this->height = height;

	this->frameTime = 1.0 / framerate;
	this->renderingEngine = new RenderEngine();

	isRunning = false;
}

CoreEngine::~CoreEngine()
{
	//See CleanUp();
}

void CoreEngine::start()
{
	if (isRunning)
		return;

	//game only kicks in once the graphics stuff has been loaded.
	//game = new Game();
	game->SetInputManager(inputManager);
	game->Initialize();

	//start game loop
	run();
}

