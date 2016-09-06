#pragma once
#include "Core.h"
#include <tchar.h>
#include <SDL_ttf.h>

class InputManager;
class Window
{
public:
	Window();
	~Window();

	void CreateWindow(int width, int height, TCHAR* title);
	void Render();
	void Close();
	void DrawText(string text);
	bool IsCloseRequested();
	int GetWidth();
	int GetHeight();
	Vector2 GetCenter();

	//
	void BindAsRenderTarget();

	bool LoadImage(SDL_Surface *& image, TCHAR* path);
	bool SetInputManager(InputManager *& inputManager);

	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;

	//The surface contained by the window
	SDL_Surface* gScreenSurface = NULL;

	//The image we will load and show on the screen
	SDL_Surface* gHelloWorld = NULL;

	//The window renderer
	SDL_Renderer* gRenderer = NULL;

	//Globally used font
	TTF_Font *gFont = NULL;

	//OpenGL context
	SDL_GLContext gContext;

private:
	bool isCloseRequested = false;
	InputManager* inputManager;
	int width;
	int height;

}; 

