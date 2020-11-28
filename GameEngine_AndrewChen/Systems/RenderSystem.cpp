#include "RenderSystem.h"

RenderSystem::RenderSystem(void)
{
}

RenderSystem::~RenderSystem(void)
{
}

void RenderSystem::tick(ECS::World* world, float delTime)
{
	Engine::GetInstance().window->clear();
	world->each<Transform, Sprite2D>(
		[&](ECS::Entity* entity,
			ECS::ComponentHandle<Transform> transform,
			ECS::ComponentHandle<Sprite2D> sprite
			) -> void 
		{
			if (textureMap.count(sprite->texture) < 1) {
				textureMap[sprite->texture] = LoadTexture(sprite->texture);
			}
			// Add texture
			if (sprite->sprite.getTexture() == nullptr) {
				sprite->sprite.setTexture(*textureMap[sprite -> texture]);
				sprite->width = sprite->sprite.getGlobalBounds().width;
				sprite->height = sprite->sprite.getGlobalBounds().height;
			}
			sprite->sprite.setPosition(transform->x,transform->y);
			sprite->sprite.setRotation(transform->rotation);
			Engine::GetInstance().window->draw(sprite->sprite);
		}
		
	);
	Engine::GetInstance().window->display();
}

sf::Texture* RenderSystem::LoadTexture(std::string filePath)
{
	sf::Texture* texture = new sf::Texture();
	if (!texture->loadFromFile(filePath)) {
		std::cerr << "Error: " << filePath << " Not Found!\nPlease correct this error." << std::endl;
		system("pause");
		exit(EXIT_FAILURE);
	}
	return texture;
}
