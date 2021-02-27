#include "Engine.h"
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
	pauseMenu = PauseMenu(this->window);
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
	system("cls");
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
			exit(EXIT_SUCCESS);
			break;
			//case sf::Event::KeyPressed:
				//cout << "Yes";
			//	break;
			//default:
				//break;
		}
		pauseMenu.update(event, 1.0f, window);
	}
	world->tick(1.0f);
	camera.update(world, 1.0f, window);
	if (States::getPauseState())
	{
		gameInactiveStateActions();
	}
}

void Engine::gameInactiveStateActions()
{
	pauseMenu.render(window, 1.0f, camera.view.getCenter());
}
