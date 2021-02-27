#pragma once
#include "../Engine.h"

class InputSystem : public ECS::EntitySystem
{
public:
	InputSystem(sf::RenderWindow* window);
	~InputSystem();
	void tick(ECS::World* world, float deltaTime)override;
	void getKey(ECS::World* world);
	bool getJoyAxis(float f);
private:
	sf::RenderWindow* window;
};

