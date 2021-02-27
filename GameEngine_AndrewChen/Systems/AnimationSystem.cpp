#include "AnimationSystem.h"
#include "../Interface/States.h"

AnimationSystem::AnimationSystem(void)
{
}

AnimationSystem::~AnimationSystem(void)
{
}

void AnimationSystem::tick(ECS::World* world, float deltaTime)
{
	if (!States::getPauseState())
	{
		world->each<Animator, Sprite2D>(
			[&](ECS::Entity* entity,
				ECS::ComponentHandle<Animator> animator,
				ECS::ComponentHandle<Sprite2D> sprite
				) -> void
			{
				sprite->sprite.setTextureRect(
					sf::IntRect(animator->currColumn * animator->frameWidth,
						animator->currRow * animator->frameHeight,
						animator->frameWidth,
						animator->frameHeight)
				);
			});
	}
}