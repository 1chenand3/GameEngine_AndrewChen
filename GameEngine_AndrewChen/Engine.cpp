#include "Engine.h"

Engine::Engine(void)
{
}

Engine::~Engine(void)
{
}
Engine& Engine::GetInstance(void)
{
	static Engine instance;
	return instance;
}

void Engine::Start(sf::RenderWindow* window)
{
	bQuit = false;
	this -> window = window;
	while (this -> window -> isOpen()) 
	{
		Update();
	}
}

void Engine::Update()
{
	sf::Event event;
	while (window -> pollEvent(event)) // Any event occur
	{
		// close event
		//if (event.type == sf::Event::Closed) window.close();
		switch (event.type)
		{
		case sf::Event::Closed:
			window -> close();
			break;
		case sf::Event::KeyPressed:
			//cout << "Yes";
			break;
		default:
			break;
		}
	}
}
