#include "Tile.h"

Tile::Tile() = default;

Tile::~Tile() = default;

Tile::Tile(float x, float y, float gridSize, bool colliding)
{
	this->shape.setSize(sf::Vector2f(gridSize, gridSize));
	this->shape.setFillColor(sf::Color(0, 0, 0));
	this->shape.setPosition(x * gridSize, y * gridSize);
	this->colliding = colliding;
}

void Tile::render(sf::RenderTarget & target)
{
	target.draw(shape);
}

const bool& Tile::getCollision() const
{
	return this->colliding;
}

const sf::Vector2f& Tile::getPosition() const
{
	return this->shape.getPosition();
}

std::string Tile::toString()
{
	std::stringstream stringForm;
	stringForm << this->colliding << " ";
	return stringForm.str();
}
