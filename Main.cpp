#include "Main.h"
#include "CoreEngine.h"
#include "Game.h"

int main(int argc, char **argv)
{
	CoreEngine* engine = new CoreEngine(WINDOW_WIDTH, WINDOW_HEIGHT, FRAMES_PER_SECOND, new Game());
	engine->CreateWindow("OpenGL Rendering Framework - Nick");
	engine->start();
	
	delete engine;
	//cin.get();
	return 1;
}
