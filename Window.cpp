#include "Window.h"
#include <iostream>
#include "InputManager.h"

Window::Window()
{
}


Window::~Window()
{
}

void Window::CreateWindow(int width, int height, TCHAR* title)
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//properties
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		//SDL_GL_GetCurrentContext();
		//Use OpenGL 2.1
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		//Create window
		gWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		
			gContext = SDL_GL_CreateContext(gWindow);
			if (gContext == NULL)
			{
				printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
			}
			
				//Initialize GLEW //modernopengl3
				glewExperimental = GL_TRUE;
				GLenum glewError = glewInit();
				if (glewError != GLEW_OK)
				{
					printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
				}

				//Use Vsync
				if (SDL_GL_SetSwapInterval(1) < 0)
				{
					printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
				}
		}
}

void Window::Render()
{
	//Get window surface
	gScreenSurface = SDL_GetWindowSurface(gWindow);

	//EVENT LOOP

	SDL_Event e;

	//core event loop, 1 frame of the rendering, outer loop in Main.cpp

		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				isCloseRequested = true;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				if (inputManager == nullptr)
					return;
				//SDL_SCANCODE_UP etc
				inputManager->KeyDown(e.key.keysym.scancode);
			}
			else if (e.type == SDL_KEYUP)
			{
				if (inputManager == nullptr)
					return;
				inputManager->KeyUp(e.key.keysym.scancode);
			}
			else if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				if (inputManager == nullptr) //TODO:Improve always calling InputManager
					return;
				inputManager->SetMouseDown(true);
			}
			else if (e.type == SDL_MOUSEBUTTONUP)
			{
				if (inputManager == nullptr) //TODO:Improve always calling InputManager
					return;
				inputManager->SetMouseDown(false);
			}
			else if (e.type == SDL_MOUSEMOTION)
			{
				if (inputManager == nullptr) //TODO:Improve always calling InputManager
					return;
				inputManager->SetMousePosition(e.motion.x,e.motion.y);
			}
		}

		//RenderModelTest();
		//renderQuad();

		//update screen
		SDL_GL_SwapWindow(gWindow);

		//Apply the image
		//SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);

		//Update the surface
		//SDL_UpdateWindowSurface(gWindow);
}

void Window::Close()
{
	//Destroy window
	SDL_DestroyWindow(gWindow);

	//Quit SDL subsystems
	SDL_Quit();

	SDL_FreeSurface(gHelloWorld);
	gHelloWorld = NULL;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

bool Window::IsCloseRequested()
{
	return isCloseRequested;
}

int Window::GetWidth()
{
	SDL_DisplayMode* mode = nullptr;
	SDL_GetDisplayMode(0, 0, mode);
	if (mode != nullptr)
		return mode->w;
	return 0;
}

int Window::GetHeight()
{
	SDL_DisplayMode* mode = nullptr;
	SDL_GetDisplayMode(0, 0, mode);
	if (mode != nullptr)
		return mode->h;
	return 0;
}

bool Window::LoadImage(SDL_Surface *& image, TCHAR* path)
{
	bool result = true;

	image = SDL_LoadBMP(path);
	if (image == NULL)
		result = false;

	return result;
}

bool Window::SetInputManager(InputManager *& inputManager)
{
	this->inputManager = inputManager;
	return false;
}
