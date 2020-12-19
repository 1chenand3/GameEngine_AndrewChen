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
	float rectLeft = rect.getPosition().x;
	float rectRight = rectLeft + rect.getGlobalBounds().width;
	float rectTop = rect.getPosition().y;
	float rectBottom = rectTop + rect.getGlobalBounds().height;
	if (main->right + x >= rectLeft && main->left + x <= rectRight) {
		// Vertical
		if (main->bottom + y >= rectTop && main->top + y <= rectBottom) {
			return true;
		}
	}
	return false;
}

bool PhysicsSystem::collided(ECS::ComponentHandle<CollisionBox> main, ECS::ComponentHandle<CollisionBox> touched)
{
	return false;
}

void PhysicsSystem::checkCollisionSide(ECS::ComponentHandle<Transform> transform, ECS::ComponentHandle<CollisionBox> main, ECS::ComponentHandle<CollisionBox> touched)
{
}

void PhysicsSystem::checkCollisionSide(ECS::ComponentHandle<Transform> transform, ECS::ComponentHandle<CollisionBox> main, sf::RectangleShape rect)
{
}

void PhysicsSystem::checkCollisionSide(ECS::Entity* main, ECS::Entity* touched)
{
}

void PhysicsSystem::tick(ECS::World* world, float deltaTime)
{
}
