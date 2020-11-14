#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ECS.h"

struct Transform
{
public:
	 ECS_DECLARE_TYPE;
	 float x, y, rotation, xScale, yScale;
	 Transform(float x, float y) {
		 this->x = x;
		 this->y = y;
		 this->rotation = .0f;
	 }
};
ECS_DEFINE_TYPE(Transform);
struct Sprite2D
{
public:
	ECS_DECLARE_TYPE;
	sf::Sprite sprite;
	std::string texture; // File path
	unsigned int width, height;
	Sprite2D() {//int width, int height

	}
};
ECS_DEFINE_TYPE(Sprite2D);