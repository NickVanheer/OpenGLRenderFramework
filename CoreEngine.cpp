#include "Core.h"
#include "CoreEngine.h"
#include "Window.h"
#include "RenderEngine.h"
#include <thread>
#include <chrono> 

void CoreEngine::CreateWindow(string title)
{
	m_window->CreateWindow(m_width, m_height, "OpenGL Renderer");
	this->renderingEngine = new RenderEngine();
	this->m_game->SetMainCamera(this->renderingEngine->GetMainCamera());
	this->renderingEngine->SetMainWindow(m_window);
}

void CoreEngine::run()
{
	m_isRunning = true;
	m_game->Initialize();

	//
	double lastTime = m_time->getTime();
	double lastDrawTime = 0;
	double unprocessedTime = m_frameTime;
	int frames = 0;
	double frameCounter = 0;
	bool drawnFirstFrame = false;

	GameContext gameContext = GameContext();
	gameContext.renderEngine = renderingEngine;

	float timeCache = 0;
	while (m_isRunning)
	{
		if (m_window->IsCloseRequested())
			stop();

		double frameDelta = m_time->getTime() - lastTime; //time between the last 2 frames
		lastTime = m_time->getTime();

		timeCache += frameDelta;

		if (timeCache > 0.01666f)
		{
			double drawDelta = 0.016666f;
			//
			gameContext.deltaTime = drawDelta;
			m_game->Input(gameContext);
			m_game->Update(gameContext);
			//cout << frameDelta << endl;
			renderingEngine->Render(m_game->GetRoot(), gameContext);
			drawnFirstFrame = true;

			timeCache = 0;
		}

		m_window->Render();
	}
}

CoreEngine::CoreEngine(int width, int height, int framerate, BaseGame* game) 
	: m_isSingleFrame(false), m_time(new Time()), m_game(game), m_isRunning(false), m_frameTime(1.0 / framerate), m_frameRate(framerate), m_width(width), m_height(height)
{
	m_inputManager = std::make_shared<InputManager>();

	m_window = std::make_shared<Window>();
	m_window->SetInputManager(m_inputManager);
}

CoreEngine::~CoreEngine()
{
	cleanUp();
}

void CoreEngine::stop()
{
	if (!m_isRunning)
		return;

	m_isRunning = false;
}

void CoreEngine::cleanUp()
{
	delete m_game;
	m_window->Close();
}

void CoreEngine::start()
{
	if (m_isRunning)
		return;

	//game only kicks in once the graphics stuff has been loaded.
	m_game->SetInputManager(m_inputManager);

	//start game loop
	run();
}

