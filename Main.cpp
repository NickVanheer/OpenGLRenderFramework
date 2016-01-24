#include "Core.h"
#include "Main.h"
#include "Window.h"
#include "Time.h"
#include "Game.h"
#include "InputManager.h"
#include <iostream>


const double Main::FRAME_CAP =  5000.0;
void Main::stop()
{
	if (!isRunning)
		return;

	isRunning = false;
}

void Main::cleanUp()
{
	game->Cleanup();
	window->Close();
}

void Main::render()
{
	RenderUtil::ClearScreen();
	game->Render();
	window->Render();
}

void Main::run()
{
	isRunning = true;
	int frames = 0;
	long frameCounter = 0;
	
	double frameTime = 1.0 / FRAME_CAP;

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
			render();
			frames++;
		}
		else
		{
			//thread.sleep(1); //less wasting
		}
	
	}
}

Main::Main()
{
	inputManager = new InputManager();

	window = new Window();
	window->SetInputManager(inputManager);

	time = new Time();
	isRunning = false;
}

Main::~Main()
{
	//See CleanUp();
}

void Main::start()
{


	if (isRunning)
		return;
	//initialize stuff (most of it happens in the constructor)
	
	//create window
	window->CreateWindow(1280, 720, "OpenGL Renderer");

	//initialize graphics //rendercontext gets created
	RenderUtil::InitGraphics();

	std::cout << RenderUtil::GetOpenGLVersion();

	//game only kicks in once the graphics stuff has been loaded.
	game = new Game();
	game->SetInputManager(inputManager);
	game->Start();

	//start game loop
	run();
}

int main(int argc, char **argv) {

	Main* m = new Main();

	m->start();

	m->cleanUp();
	cin.get();
	return 1;
}
