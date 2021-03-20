#include "PhysicsSystem.h"
#include "../Interface/States.h"

PhysicsSystem::PhysicsSystem()
{
}

PhysicsSystem::~PhysicsSystem()
{
}
// Add struct before CollisionBox
bool PhysicsSystem::collided(ECS::ComponentHandle<struct CollisionBox> main, ECS::ComponentHandle<struct CollisionBox> touched, float x, float y)
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

bool PhysicsSystem::collided(ECS::ComponentHandle<struct CollisionBox> main, sf::RectangleShape rect, float x, float y)
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

bool PhysicsSystem::collided(ECS::ComponentHandle<CollisionBox> main, sf::RectangleShape rect)
{
	float _touchedRectLeft = rect.getPosition().x;
	float _touchedRectRight = _touchedRectLeft + rect.getGlobalBounds().width;
	float _touchedRectTop = rect.getPosition().y;
	float _touchedRectBottom = _touchedRectTop + rect.getGlobalBounds().height;

	return main->right > _touchedRectLeft &&
		_touchedRectRight > main->left &&
		main->bottom > _touchedRectTop &&
		_touchedRectBottom > main->top;

}

bool PhysicsSystem::collided(ECS::ComponentHandle<struct CollisionBox> main, ECS::ComponentHandle<struct CollisionBox> touched)
{
	return main->right > touched->left && touched->right > main->left && main->bottom > touched->top && touched->bottom > main->top;
}

void PhysicsSystem::checkCollisionSide(ECS::ComponentHandle<struct Transform> transform, ECS::ComponentHandle<struct CollisionBox> main, ECS::ComponentHandle<struct CollisionBox> touched)
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

void PhysicsSystem::checkCollisionSide(ECS::ComponentHandle<struct Transform> transform, ECS::ComponentHandle<struct CollisionBox> main, sf::RectangleShape rect)
{
	float rectLeft = rect.getPosition().x;
	float rectRight = rectLeft + rect.getGlobalBounds().width;
	float rectTop = rect.getPosition().y;
	float rectBottom = rectTop + rect.getGlobalBounds().height;
	// Going Right
	if (transform->xSpeed > 0 && main->right + transform->xSpeed > rectLeft &&
		main->left < rectRight && 
		main->top < rectBottom && main->bottom>rectTop) {
		transform->xSpeed = 0;
		transform->x = rectLeft - 56;
		transform->collision = true;
	}

	// Going Left
	if (transform->xSpeed < 0 && main->left + transform->xSpeed < rectRight && 
		main->right > rectLeft &&
		main->top < rectBottom && main->bottom>rectTop) {
		transform->xSpeed = 0;
		transform->x = rectRight;
		transform->collision = true;
	}

	// Going Down
	if (transform->ySpeed > 0 && main->bottom + transform->ySpeed > rectTop && 
		main->top < rectBottom &&
		main->left < rectRight && main->right>rectLeft) {
		transform->ySpeed = 0;
		transform->y = rectTop - 72;
		transform->collision = true;
	}

	// Going Up
	if (transform->ySpeed < 0 && main->top + transform->ySpeed < rectBottom && 
		main->bottom > rectTop &&
		main->left < rectRight && main->right>rectLeft) {
		transform->ySpeed = 0;
		transform->y = rectBottom;
		transform->collision = true;
	}
}

void PhysicsSystem::push(ECS::Entity* main, ECS::Entity* touched)
{
	float mainX = main->get<struct Transform>()->x, mainY = main->get<struct Transform>()->y;
	float touchedX = touched->get<struct Transform>()->x, touchedY = touched->get<struct Transform>()->y;
	float xSpeed = main->get<struct Transform>()->xSpeed;
	float ySpeed = main->get<struct Transform>()->ySpeed;

	// Speed for touched?
	//touched->get<Transform>()->x += signOf(xSpeed);
	//touched->get<Transform>()->y += signOf(ySpeed);

	if (xSpeed > 0 && mainX < touchedX) {
		//touched->get<struct Transform>()->x++;
		//touched->get<struct Transform>()->x += main->get<Transform>()->speedMod;
		touched->get<struct Transform>()->x = main->get<CollisionBox>()->right;
	}
	else if (xSpeed < 0 && mainX > touchedX) {
		//touched->get<struct Transform>()->x--;
		//touched->get<struct Transform>()->x -= main->get<Transform>()->speedMod;
		touched->get<struct Transform>()->x = main->get<CollisionBox>()->left - touched->get<CollisionBox>()->width;
	}

	if (ySpeed > 0 && mainY < touchedY) {
		//touched->get<struct Transform>()->y++;
		//touched->get<struct Transform>()->y += main->get<Transform>()->speedMod;
		touched->get<struct Transform>()->y = main->get<CollisionBox>()->bottom;
	}
	else if (ySpeed < 0 && mainY > touchedY) {
		//touched->get<struct Transform>()->y--;
		//touched->get<struct Transform>()->y -= main->get<Transform>()->speedMod;
		touched->get<struct Transform>()->y = main->get<CollisionBox>()->top - touched->get<CollisionBox>()->height;
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
	if (!States::getPauseState())
	{
		world->each<struct CollisionBox, struct Sprite2D, struct Transform>(
			[&](ECS::Entity* entity, ECS::ComponentHandle<struct CollisionBox> box, ECS::ComponentHandle<Sprite2D> sprite, ECS::ComponentHandle<struct Transform> transform
				) -> void {
					box->update(transform->x, transform->y, sprite->sprite.getTextureRect().width, sprite->sprite.getTextureRect().height);
			});

		world->each<struct CollisionBox, struct Transform>(
			[&](ECS::Entity* main, ECS::ComponentHandle<struct CollisionBox> mainBox, ECS::ComponentHandle<struct Transform> transform1
				) -> void {
					world->each<struct CollisionBox>(
						[&](ECS::Entity* touchedEntity, ECS::ComponentHandle<struct CollisionBox> touchedBox) -> void {
							// Avoid same entity
							if (main->getEntityId() == touchedEntity->getEntityId()) {
								return;
							}
							if (!collided(mainBox, touchedBox)) {
								return;
							}
							push(main, touchedEntity);
						});
					world->each<struct TileMap>(
						[&](ECS::Entity* tileMapE, ECS::ComponentHandle<struct TileMap> tileMap
							) -> void {
								transform1->collision = false;
								for (auto& x : tileMap->map) {
									for (auto& y : x) {
										for (auto& z : y) {
											if (z == nullptr || !z->colliding) { continue; }
											// Check future position
											//if (collided(mainBox, z->shape, transform1->xSpeed, transform1->ySpeed)) {
												
												//transform1->collision = true;
												//std::cout << "Collided\n"; 
												checkCollisionSide(transform1, mainBox, z->shape);
											//}
										}
									}
								}
						});
			});

		world->each<struct Transform>(
			[&](ECS::Entity* entity, ECS::ComponentHandle<struct Transform> transform)->void {transform->move(); });
		std::cout << "Physic Tick\n";
	}
}
