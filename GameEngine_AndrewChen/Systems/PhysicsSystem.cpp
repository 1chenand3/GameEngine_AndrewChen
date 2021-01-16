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
	return main->right > touched->left && touched->right > main->left && main->bottom > touched->top && touched->bottom > main->top;
}

void PhysicsSystem::checkCollisionSide(ECS::ComponentHandle<Transform> transform, ECS::ComponentHandle<CollisionBox> main, ECS::ComponentHandle<CollisionBox> touched)
{
	// Going Right
	if (transform->xSpeed > 0 && main->right + transform->xSpeed > touched->left && main->top < touched->bottom && main->bottom>touched->top) {
		transform->xSpeed = 0;
	}

	// Going Left
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

	// Going Left
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

	// Speed for touched?
	//touched->get<Transform>()->x += signOf(xSpeed);
	//touched->get<Transform>()->y += signOf(ySpeed);

	if (xSpeed > 0 && mainX <= touchedX) {
		touched->get<Transform>()->x++;
	}
	else if (xSpeed < 0 && mainX >= touchedX) {
		touched->get<Transform>()->x--;
	}

	if (ySpeed > 0 && mainY <= touchedY) {
		touched->get<Transform>()->y++;
	}
	else if (ySpeed < 0 && mainY >= touchedY) {
		touched->get<Transform>()->y--;
	}
}

int signOf(double d) {
	if (d < 0) {
		return -1;
	}
	else if (d > 0) {
		return 1;
	}
	return 0;
}

void PhysicsSystem::tick(ECS::World* world, float deltaTime)
{
	world->each<CollisionBox, Sprite2D, Transform>(
		[&](ECS::Entity* entity, ECS::ComponentHandle<CollisionBox> box, ECS::ComponentHandle<Sprite2D> sprite, ECS::ComponentHandle<Transform> transform
			) -> void {
				box->update(transform->x, transform->y, sprite->sprite.getTextureRect().width, sprite->sprite.getTextureRect().height);
		});

	world->each<CollisionBox, Transform>(
		[&](ECS::Entity* main, ECS::ComponentHandle<CollisionBox> mainBox, ECS::ComponentHandle<Transform> transform1
			) -> void {
				world->each<CollisionBox, Transform>(
					[&](ECS::Entity* touched, ECS::ComponentHandle<CollisionBox> touchedBox, ECS::ComponentHandle<Transform> transform2
						) -> void {
							// Avoid same entity
							if (main->getEntityId() != touched->getEntityId()) {
								if (collided(mainBox, touchedBox)) {
									push(main, touched);
								}
							}
					});
		});
	world->each<Transform>(
		[&](ECS::Entity* entity, ECS::ComponentHandle<Transform> transform)->void {transform->move(); });
}
