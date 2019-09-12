#pragma once
#include "Core.h"
class InputManager
{
public:
	InputManager();
	virtual ~InputManager();
	InputManager(const InputManager& copy) = delete;
	InputManager& operator=(const InputManager& assignment) = delete;

	void KeyDown(unsigned int);
	void KeyUp(unsigned int);

	bool IsKeyDown(unsigned int);
	bool IsMouseDown();
	bool IsMouseUp();
	void SetMouseDown(bool);
	void SetMousePosition(int, int);
	void SetMousePosition(Vector2 pos);
	void SetMouseEnabled(bool enabled);

	void SetWindow(SDL_Window* window);
	int GetMouseX();
	int GetMouseY();

	static InputManager& GetInstance();
private:
	bool keys[256];
	bool isMouseDown;
	int mouseX, mouseY;
	SDL_Window* window;

};

