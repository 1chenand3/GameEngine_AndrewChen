#include "MovementSystem.h"
#include "../Interface/States.h"

//#define X_SPEED 0.2
//#define Y_SPEED 0.2

MovementSystem::MovementSystem()
{
}

MovementSystem::~MovementSystem()
{
}

void MovementSystem::tick(ECS::World* world, float deltaTime)
{
	if (!States::getPauseState())
	{
		world->each<InputControl, Transform, Animator>(
			[&](ECS::Entity* entity,
				ECS::ComponentHandle<InputControl> input,
				ECS::ComponentHandle<Transform> transform,
				ECS::ComponentHandle<Animator> animator) -> void {
					if (input->inputActive) {
						if (input->up) {
							transform->ySpeed = -transform->speedMod;
						}
						else if (input->down) {
							transform->ySpeed = transform->speedMod;
						}
						else transform->ySpeed = 0;

						if (input->left) {
							animator->facingRight = false;
							animator->currRow = 1;
							transform->xSpeed = -transform->speedMod;
						}
						else if (input->right) {
							animator->facingRight = true;
							animator->currRow = 1;
							transform->xSpeed = transform->speedMod;
						}
						else {
							animator->currRow = 0;
							transform->xSpeed = 0;
						}
						transform->move();
					}
					//std::cout << transform->speedMod;
					//std::cout << "\n";

			});
	}
}