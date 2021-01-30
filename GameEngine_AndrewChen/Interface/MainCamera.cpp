#include "MainCamera.h"

MainCamera::MainCamera()
{
}

MainCamera::MainCamera(sf::Vector2f pivot)
{
	view.setCenter(pivot);
}

MainCamera::~MainCamera()
{
}

void MainCamera::update(ECS::World* world, float deltaTime, sf::RenderWindow* gameWindow)
{
	float cameraSpeed = 0.1f;
	// Define new vector 
	sf::Vector2f windowSize(gameWindow->getSize().x, gameWindow->getSize().y);
	view.setSize(windowSize);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		view.move(-cameraSpeed * deltaTime, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		view.move(cameraSpeed * deltaTime, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		view.move(0, -cameraSpeed * deltaTime);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		view.move(0, cameraSpeed * deltaTime);
	}

	gameWindow->setView(view);
}
