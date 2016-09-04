#include "Main.h"
#include "CoreEngine.h"
#include "Game.h"

Main::Main()
{
}


Main::~Main()
{
}

int main(int argc, char **argv)
{
	CoreEngine* engine = new CoreEngine(WINDOW_WIDTH, WINDOW_HEIGHT, FRAMES_PER_SECOND, new Game());
	engine->CreateWindow("OpenGL Rendering Framework");
	engine->start();
	
	delete engine;
	//cin.get();
	return 1;
}
