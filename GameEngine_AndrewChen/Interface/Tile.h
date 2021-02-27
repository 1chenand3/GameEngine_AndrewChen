#pragma once
#include <sstream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
class Tile
{
public:
	bool colliding;
	sf::RectangleShape shape;
	Tile();
	~Tile();
	Tile(float x, float y, float gridSize, bool colliding);
	void render(sf::RenderTarget& target);
	const bool& getCollision() const;
	const sf::Vector2f& getPosition() const;
	std::string toString();
};

