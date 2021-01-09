#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem()
{
}

PhysicsSystem::~PhysicsSystem()
{
}

bool PhysicsSystem::collided(ECS::ComponentHandle<CollisionBox> main, ECS::ComponentHandle<CollisionBox> touched, float x, float y)
{
	//  TODO: change everything into one return statement
	// horizontal
	if (main->right + x >= touched->left && main->left + x <= touched->right) {
		// Vertical  
		if (main->bottom + y >= touched->top && main->top + y <= touched->bottom) {
			return true;
		}
	}
	return false;
}

bool PhysicsSystem::collided(ECS::ComponentHandle<CollisionBox> main, sf::RectangleShape rect, float x, float y)
{
	//  TODO: change everything into one return statement
	float rectLeft = rect.getPosition().x;
	float rectRight = rectLeft + rect.getGlobalBounds().width;
	float rectTop = rect.getPosition().y;
	float rectBottom = rectTop + rect.getGlobalBounds().height;
	if (main->right + x >= rectLeft && main->left + x <= rectRight) {
		if (main->bottom + y >= rectTop && main->top + y <= rectBottom) {
			return true;
		}
	}
	return false;
}

bool PhysicsSystem::collided(ECS::ComponentHandle<CollisionBox> main, ECS::ComponentHandle<CollisionBox> touched)
{
	return main->right > touched->left && touched->right > main->left && main->bottom > touched->top && touched->bottom > touched->top;
}

void PhysicsSystem::checkCollisionSide(ECS::ComponentHandle<Transform> transform, ECS::ComponentHandle<CollisionBox> main, ECS::ComponentHandle<CollisionBox> touched)
{
	// Going Right
	if (transform->xSpeed > 0 && main->right + transform->xSpeed > touched->left && main->top < touched->bottom && main->bottom>touched->top) {
		transform->xSpeed = 0;
	}

	// Going left
	if (transform->xSpeed < 0 && main->left + transform->xSpeed < touched->right && main->top < touched->bottom && main->bottom>touched->top) {
		transform->xSpeed = 0;
	}

	// Going Down
	if (transform->ySpeed > 0 && main->bottom + transform->ySpeed > touched->top && main->left < touched->right && main->right>touched->left) {
		transform->ySpeed = 0;
	}

	// Going Up
	if (transform->ySpeed < 0 && main->top + transform->ySpeed < touched->bottom && main->left < touched->right && main->right>touched->left) {
		transform->ySpeed = 0;
	}
}

void PhysicsSystem::checkCollisionSide(ECS::ComponentHandle<Transform> transform, ECS::ComponentHandle<CollisionBox> main, sf::RectangleShape rect)
{
	float rectLeft = rect.getPosition().x;
	float rectRight = rectLeft + rect.getGlobalBounds().width;
	float rectTop = rect.getPosition().y;
	float rectBottom = rectTop + rect.getGlobalBounds().height;
	// Going Right
	if (transform->xSpeed > 0 && main->right + transform->xSpeed > rectLeft && main->top < rectBottom && main->bottom>rectTop) {
		transform->xSpeed = 0;
	}

	// Going left
	if (transform->xSpeed < 0 && main->left + transform->xSpeed < rectRight && main->top < rectBottom && main->bottom>rectTop) {
		transform->xSpeed = 0;
	}

	// Going Down
	if (transform->ySpeed > 0 && main->bottom + transform->ySpeed > rectTop && main->left < rectRight && main->right>rectLeft) {
		transform->ySpeed = 0;
	}

	// Going Up
	if (transform->ySpeed < 0 && main->top + transform->ySpeed < rectBottom && main->left < rectRight && main->right>rectLeft) {
		transform->ySpeed = 0;
	}
}

void PhysicsSystem::push(ECS::Entity* main, ECS::Entity* touched)
{
	float mainX = main->get<Transform>()->x, mainY = main->get<Transform>()->y;
	float touchedX = touched->get<Transform>()->x, touchedY = touched->get<Transform>()->y;
	float xSpeed = main->get<Transform>()->xSpeed;
	float ySpeed = main->get<Transform>()->ySpeed;


	if (mainX - xSpeed < touchedX - xSpeed) {
		touched->get<Transform>()->x++;
	}
	else if (mainX - xSpeed > touchedX - xSpeed) {
		touched->get<Transform>()->x--;
	}

	if (mainY - ySpeed < touchedY - ySpeed) {
		touched->get<Transform>()->y++;
	}
	else if (mainY - ySpeed > touchedY - ySpeed) {
		touched->get<Transform>()->y--;
	}
}

void PhysicsSystem::tick(ECS::World* world, float deltaTime)
{
}
