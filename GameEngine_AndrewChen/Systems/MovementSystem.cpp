#include "MovementSystem.h"

#define X_SPEED 0.2
#define Y_SPEED 0.2

MovementSystem::MovementSystem()
{
}

MovementSystem::~MovementSystem()
{
}

void MovementSystem::tick(ECS::World* world, float deltaTime)
{
	world->each<InputControl, Transform, Animator>(
		[&](ECS::Entity* entity,
			ECS::ComponentHandle<InputControl> input,
			ECS::ComponentHandle<Transform> transform,
			ECS::ComponentHandle<Animator> animator) -> void {
				if (input->inputActive) {
					if (input->w) {
						transform->ySpeed = -Y_SPEED;
						transform->move();
					}
					else if (input->s) { 
						transform->ySpeed = Y_SPEED; 
						transform->move();
					}
					else transform->ySpeed = 0;

					if (input->a) {
						animator->facingRight = false;
						animator->currRow = 1;
						transform->xSpeed = -X_SPEED;
						transform->move();
					}
					else if (input->d) {
						animator->facingRight = true;
						animator->currRow = 1;
						transform->xSpeed = X_SPEED;
						transform->move();
					}
					else {
						animator->currRow = 0;
						transform->xSpeed = 0;
					}
				}
		});
}
