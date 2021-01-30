#pragma once

#include <SFML/Graphics.hpp>
#include "../ECS.h"

class MainCamera
{
public:
	sf::View view;
	MainCamera();
	MainCamera(sf::Vector2f pivot);
	~MainCamera();
	void update(ECS::World* world, float deltaTime, sf::RenderWindow* gameWindow);
};

