#pragma once

#include "../Engine.h"

class AnimationSystem : public ECS::EntitySystem
{
public:
	AnimationSystem(void);
	~AnimationSystem(void);
	void tick(ECS::World* world, float deltaTime)override;
};

