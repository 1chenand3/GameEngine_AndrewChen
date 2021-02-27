#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ECS.h"
#include "Components.h"

#include "Systems/RenderSystem.h"
#include "Systems/AnimationSystem.h"
#include "Systems/InputSystem.h"
#include "Systems/MovementSystem.h"
#include "Systems/PhysicsSystem.h"

#include "Interface/MainCamera.h"
#include "Interface/PauseMenu.h"
#include "Interface/States.h"
#include "Interface/ButtonMap.h"
#include "Interface/Button.h"

class Engine
{
public:
	ECS::World* world;
	sf::RenderWindow* window;

	MainCamera camera;
	PauseMenu pauseMenu;

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
	void gameInactiveStateActions();
};

