#include "pch.h"
#include "InputManager.h"

InputManager::InputManager()
{
	for (int i = 0; i<256; i++)
	{
		keys[i] = false;
	}

	isMouseDown = false;
}

InputManager::~InputManager()
{
}

void InputManager::KeyDown(unsigned int input)
{
	keys[input] = true;
}

void InputManager::KeyUp(unsigned int input)
{
	keys[input] = false;
}

bool InputManager::IsKeyDown(unsigned int key)
{
	return keys[key];
}

bool InputManager::IsMouseDown()
{
	return isMouseDown;
}

bool InputManager::IsMouseUp()
{
	return !isMouseDown;
}

void InputManager::SetMouseDown(bool result)
{
	isMouseDown = result;
}

void InputManager::SetMousePosition(int x, int y)
{
	mouseX = x;
	mouseY = y;
}

void InputManager::SetMousePosition(Vector2 pos)
{
	SDL_WarpMouseInWindow(window, pos.x, pos.y);
}

void InputManager::SetMouseEnabled(bool enabled)
{
	SDL_ShowCursor(enabled);
}

void InputManager::SetWindow(SDL_Window * window)
{
	this->window = window;
}

int InputManager::GetMouseX()
{
	return mouseX;
}

int InputManager::GetMouseY()
{
	return mouseY;
}

InputManager & InputManager::GetInstance()
{
	static InputManager instance; //only created the first time, doesn't get destroyed. 
	return instance;
}

