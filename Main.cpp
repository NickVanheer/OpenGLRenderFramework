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
	CoreEngine* engine = new CoreEngine(800,600,60, new Game());
	engine->CreateWindow("OpenGL Rendering Framework");
	engine->start();
	//m->start();
	
	//m->cleanUp();
	//cin.get();
	return 1;
}
