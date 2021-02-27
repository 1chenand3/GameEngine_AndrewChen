#include "InputSystem.h"
#include "../Interface/States.h"

InputSystem::InputSystem(sf::RenderWindow* window) : window(window)
{
}

InputSystem::~InputSystem()
{
}

void InputSystem::tick(ECS::World* world, float deltaTime)
{
	if (!States::getPauseState())
	{
		getKey(world);
		std::cout << sf::Joystick::isButtonPressed(0, 1);
		std::cout << "\n";
		std::cout << sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X);
		std::cout << "\n";
		std::cout << sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y);
		std::cout << "\n";
	}
}

void InputSystem::getKey(ECS::World* world)
{

		world->each<InputControl>(
			[&](ECS::Entity* entity,
				ECS::ComponentHandle<InputControl> input) -> void {
					//	if (sf::Joystick::isConnected(0)) {
					input->up = -sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) >= 50;
					input->down = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) >= 50;
					input->left = -sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) >= 50;
					input->right = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) >= 50;
					//}
					//else {
					//	input->uo = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
					//	input->left = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
					//	input->down = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
					//	input->right = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
					//}
			});
}
//bool getJoyAxis(float f) {
	//return f >= 50;
//}
//http://www.carvware.com/images/screenshots/XBOX360Controller.png
