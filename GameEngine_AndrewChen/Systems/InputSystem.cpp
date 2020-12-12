#include "InputSystem.h"

InputSystem::InputSystem(sf::RenderWindow* window) : window(window)
{
}

InputSystem::~InputSystem()
{
}

void InputSystem::tick(ECS::World* world, float deltaTime)
{
	getKey(world);
}

void InputSystem::getKey(ECS::World* world)
{
	world->each<InputControl>(
		[&](ECS::Entity* entity,
			ECS::ComponentHandle<InputControl> input) -> void {
				input->w = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
				input->a = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
				input->s = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
				input->d = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
		});
}
