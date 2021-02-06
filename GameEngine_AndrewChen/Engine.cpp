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
	camera = MainCamera(sf::Vector2f(
		window->getSize().x / 2,
		window->getSize().y / 2
	));
	bQuit = false;
	this->window = window;
	while (this->window->isOpen())
	{
		Update();
	}
}

void Engine::addSystem(ECS::EntitySystem* newSys)
{
	world->registerSystem(newSys);
	world->enableSystem(newSys);
}

void Engine::Update()
{
	sf::Event event;
	while (window->pollEvent(event)) // Any event occur
	{
		// close event
		// 
		// if (event.type == sf::Event::Closed) window.close();
		//
		switch (event.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
			//case sf::Event::KeyPressed:
				//cout << "Yes";
			//	break;
			//default:
				//break;
		}
	}
	world->tick(1.0f);
	camera.update(world, 1.0f, window);
}
