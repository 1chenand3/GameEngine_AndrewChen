#include "TileMapSystem.h"

TileMapSystem::TileMapSystem() = default;

TileMapSystem::~TileMapSystem() = default;

void TileMapSystem::tick(ECS::World * world, float deltaTime)
{
	Engine::GetInstance().world->each<TileMap>(
		[&](ECS::Entity* entity, ECS::ComponentHandle<TileMap> tileMap) -> void {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				addTileOnClick(true, tileMap);
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				addTileOnClick(false, tileMap);
			}
			if (ButtonMap::getMap()["Save"]->clicked) {
				tileMap->saveTileMap("TileTest.txt");
				ButtonMap::getMap()["Save"]->clicked = false;
			}
			if (ButtonMap::getMap()["Load"]->clicked) {
				tileMap->loadTileMap("TileTest.txt");
				ButtonMap::getMap()["Load"]->clicked = false;
			}
		});
}

void TileMapSystem::addTileOnClick(bool hasCollision, ECS::ComponentHandle<TileMap> tileMap) {
	//Reference for window pointer is used to get mouse position
	sf::RenderWindow* window = Engine::GetInstance().window;
	sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
	sf::Vector2i mouseGrid(static_cast<int>(mousePos.x / tileMap->gridSize), static_cast<int>(mousePos.y / tileMap->gridSize));
	tileMap->addTile(mouseGrid.x, mouseGrid.y, hasCollision);
}
