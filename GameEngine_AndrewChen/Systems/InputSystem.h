#pragma once
#include "../ECS.h"
#include "../Components.h"
class InputSystem : public ECS::EntitySystem
{
public:
	InputSystem(sf::RenderWindow* window);
	~InputSystem();
	void tick(ECS::World* world, float deltaTime)override;
	void getKey(ECS::World* world);
private:
	sf::RenderWindow* window;
};

