#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ECS.h"

struct Transform
{
public:
	 ECS_DECLARE_TYPE;
	 float x, y, rotation, xScale, yScale;
	 float xSpeed, ySpeed;
	 Transform(float x, float y) : x(x),y(y){
		 xSpeed = 0;
		 ySpeed = 0;
		 this->rotation = .0f;
	 }
	 void updateSpeed(float x, float y){
		 this->xSpeed = x;
		 this->ySpeed = y;
	 }
	 void move() {
		 x += xSpeed;
		 y += ySpeed;
	 }
	 void stop() {
		 xSpeed = 0;
		 ySpeed = 0;
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
	Sprite2D(std::string filePath) {//int width, int height
		texture = filePath;
	}
};
ECS_DEFINE_TYPE(Sprite2D);

struct Animator
{
public:
	ECS_DECLARE_TYPE;
	int frameWidth, frameHeight;
	int currColumn, currRow, totalColumns, totalRows;
	float currTime, nextFrame;
	bool facingRight;
	Animator(
		int newWidth,int newHeight,
		float frameWindow,
		int newColumns,int newRows) {
		this->frameWidth = newWidth;
		this->frameHeight = newHeight;
		currColumn = 0;
		currRow = 0;
		this->totalColumns = newColumns;
		this->totalRows = newRows;
		this->nextFrame = frameWindow;
		currTime = 0;
		facingRight = true;
	}
};
ECS_DEFINE_TYPE(Animator);

struct Collision
{
public:
	ECS_DECLARE_TYPE;
	float width, height;
	Collision() {//int width, int height

	}
	bool detect() {
		return true;
	}
};
ECS_DEFINE_TYPE(Collision);

struct InputControl
{
public:
	ECS_DECLARE_TYPE;
	bool inputActive;
	// Keys
	bool w,a,s,d,enter;

	InputControl() {
		inputActive = true;
		w = false;
		a = false;
		s = false;
		d = false;
		enter = false;
	}
};
ECS_DEFINE_TYPE(InputControl);