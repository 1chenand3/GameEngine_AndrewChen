#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ECS.h"
#include "Components.h"
class Engine
{
public:
	ECS::World* world;
	sf::RenderWindow* window;
	
	static Engine& GetInstance(void);

	void Start(sf::RenderWindow* window);
	void addSystem(ECS::EntitySystem* newSys);
private:
	bool bQuit;
	Engine(void);
	// Needed to prevent refrece form being changed
	Engine(Engine& copy);	// Hide copy
	Engine(Engine&& other);		// Hide move
	Engine& operator = (Engine& copy);		// Hide assignment

	~Engine(void);
	void Update();
};

