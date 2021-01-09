#pragma once
//#include "../Engine.h"
#include "../ECS.h"
#include "../Components.h"
class PhysicsSystem : ECS::EntitySystem
{
public:
	PhysicsSystem();
	~PhysicsSystem();
	bool collided(
		ECS::ComponentHandle<CollisionBox> main,
		ECS::ComponentHandle<CollisionBox> touched,
		float x, float y
	);
	bool collided(
		ECS::ComponentHandle<CollisionBox> main,
		sf::RectangleShape rect,
		float x, float y
	);
	bool collided(
		ECS::ComponentHandle<CollisionBox> main,
		ECS::ComponentHandle<CollisionBox> touched
	);
	void checkCollisionSide(
		ECS::ComponentHandle<Transform> transform,
		ECS::ComponentHandle<CollisionBox> main,
		ECS::ComponentHandle<CollisionBox> touched
	);
	void checkCollisionSide(
		ECS::ComponentHandle<Transform> transform,
		ECS::ComponentHandle<CollisionBox> main,
		sf::RectangleShape rect);
	void push(
		ECS::Entity* main,
		ECS::Entity* touched
	);
	void tick(ECS::World* world, float deltaTime) override;
};

