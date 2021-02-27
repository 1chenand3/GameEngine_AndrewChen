#pragma once

#include "../Interface/ButtonMap.h"
#include "../Engine.h"

class TileMapSystem : public ECS::EntitySystem
{
public:
	TileMapSystem();
	~TileMapSystem();
	void tick(ECS::World* world, float deltaTime);
	void addTileOnClick(bool hasCollision, ECS::ComponentHandle<TileMap> tileMap);
};