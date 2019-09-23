#include "pch.h"
#include "Main.h"
#include "CoreEngine.h"
#include "Game.h"

static const int WINDOW_WIDTH = 1280;
static const int WINDOW_HEIGHT = 768;
static const int FRAMES_PER_SECOND = 60;

int main(int argc, char **argv)
{
	CoreEngine* engine = new CoreEngine(WINDOW_WIDTH, WINDOW_HEIGHT, FRAMES_PER_SECOND, new Game());
	engine->CreateWindow("OpenGL Rendering Framework - Nick");
	engine->start();
	
	delete engine;
	return 1;
}
