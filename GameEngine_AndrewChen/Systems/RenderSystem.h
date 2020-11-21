#pragma once

#include "..\Engine.h"

class RenderSystem : public ECS::EntitySystem
{
public:
	RenderSystem(void);
	~RenderSystem(void);

	void tick(ECS::World* world,float delTime) override;
private:
	// Dynamic list with key(string) and value(texture)
	std::unordered_map<std::string, sf::Texture*> textureMap;
	sf::Texture* LoadTexture(std::string filePath);
};

