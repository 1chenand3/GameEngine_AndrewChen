#pragma once
//#include <iostream>
#include <SFML/Graphics.hpp>
#include "ECS.h"
#include "Engine.h"
#include "Interface/Tile.h"
#include <fstream>
#include <sstream>
//#include <cmath>

struct Transform
{
public:
	ECS_DECLARE_TYPE;
	float x, y, rotation; //xScale, yScale;
	float xSpeed, ySpeed, speedMod;
	Transform(float x, float y, float speedMod = 0.0f) : x(x), y(y), speedMod(speedMod) {
		xSpeed = 0;
		ySpeed = 0;
		this->rotation = .0f;
	}
	void updateSpeed(float x, float y) {
		this->xSpeed = x;
		this->ySpeed = y;
	}
	void move() {
		if (xSpeed != 0 && ySpeed != 0) {
			xSpeed /= 2;
			ySpeed /= 2;
		}
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
		int newWidth, int newHeight,
		float frameWindow,
		int newColumns, int newRows) {
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

struct CollisionBox
{
public:
	ECS_DECLARE_TYPE;
	//	float width, height;
	float left, right, top, bottom;
	float width, height;
	CollisionBox() {//int width, int height
		//left = 0;
		//right = 0;
		//top = 0;
		//bottom = 0;
		std::memset(this, '\0', sizeof(CollisionBox));
	}
	void update(float xSide, float ySide, float width, float height) {
		left = xSide;
		right = xSide + width;
		top = ySide;
		bottom = ySide + height;
		this->width = width;
		this->height = height;
	}
	bool detect() {
		return true;
	}
};
ECS_DEFINE_TYPE(CollisionBox);

struct InputControl
{
public:
	ECS_DECLARE_TYPE;
	bool inputActive;
	// Keys
	bool up, left, down, right, confirm;

	InputControl() {
		inputActive = true;
		up = false;
		left = false;
		down = false;
		right = false;
		confirm = false;
	}
};
ECS_DEFINE_TYPE(InputControl);

struct Camera
{
public:
	ECS_DECLARE_TYPE;
	sf::View view;

	Camera(sf::Vector2f pivot) {
		view.setCenter(pivot);
	}
};
ECS_DEFINE_TYPE(Camera);

struct TileMap
{
public:
	ECS_DECLARE_TYPE;
	float gridSize; // For setting the size
	uint32_t gridSizeU; // 
	uint32_t layer; // Rendering in order
	sf::Vector2u maxSize; // set the size
	sf::RectangleShape collisionBox;

	std::vector<std::vector<std::vector<Tile*>>> map;

	TileMap() {
		this->gridSize = 50;
		this->gridSizeU = static_cast<uint32_t>(this->gridSize);
		this->maxSize.x = 20;
		this->maxSize.y = 20;
		this->layer = 1;
		this->map.resize(this->maxSize.x);
		for (size_t x = 0; x < this->maxSize.x; x++) {
			this->map.push_back(std::vector<std::vector<Tile*>>());

			for (size_t y = 0; y < this->maxSize.y; y++) {
				this->map.at(x).resize(this->maxSize.y);
				this->map.at(x).push_back(std::vector<Tile*>());

				for (size_t z = 0; z < this->layer; z++) {
					this->map.at(x).at(y).resize(this->layer);
					this->map.at(x).at(y).push_back(nullptr);
				}
			}
		}
		this->collisionBox.setSize(sf::Vector2f(this->gridSize, this->gridSize));
		this->collisionBox.setFillColor(sf::Color::Magenta);
		this->collisionBox.setOutlineColor(sf::Color::Green);
		this->collisionBox.setOutlineThickness(1);

	}

	~TileMap()
	{
		clear();
	}

	void addTile(const int x, const int y, const int z, bool hasCollision) {
		std::cout << x << " " << y << " " << z << "\n";
		if (x < this->maxSize.x && x >= 0 &&
			y < this->maxSize.y && y >= 0 &&
			z < this->layer && z >= 0) {
			std::cout << this->maxSize.x << " " << this->maxSize.y << " " << this->layer << "\n";
			if (this->map[x][y][z] == nullptr) {
				// Cant reach here
				this->map[x][y][z] = new Tile(x, y, this->gridSize, hasCollision);
				std::cout << "Added tile - by andrew \n";
			}
			else {
				std::cout << "failed.";
			}
		}
	}
	void clear() {
		for (size_t x = 0; x < this->maxSize.x; x++) {
			for (size_t y = 0; y < this->maxSize.y; y++) {
				for (size_t z = 0; z < this->layer; z++) {
					delete this->map[x][y][z];
				}
				this->map[x][y].clear();
			}
			this->map[x].clear();
		}
		this->map.clear();
	}

	void saveTileMap(std::string fileName) {
		std::ofstream saveFile;
		saveFile.open(fileName);
		if (saveFile.is_open()) {

			saveFile << maxSize.x << " " << maxSize.y << "\n" << gridSize << "\n" << layer << "\n";

			for (size_t x = 0; x < this->maxSize.x; x++) {
				for (size_t y = 0; y < this->maxSize.y; y++) {
					for (size_t z = 0; z < this->layer; z++) {
						if (this->map[x][y][z] != nullptr) {
							saveFile << x << " " << y << " " << this->map[x][y][z]->toString() << "\n";
						}
					}
				}
			}
		}
		else {
			std::cout << "Cannot save " << fileName << "\n";
		}
		saveFile.close();
	}
	void loadTileMap(std::string fileName) {
		std::ifstream loadFile;
		loadFile.open(fileName);
		if (loadFile.is_open()) {
			unsigned int x = maxSize.x, y = maxSize.y, z = layer;
			bool colliding = false;
			loadFile >> x >> y >> gridSize >> z;
			this->clear();
			this->map.resize(this->maxSize.x, std::vector<std::vector<Tile*>>());

			for (size_t x = 0; x < this->maxSize.x; x++) {
				for (size_t y = 0; y < this->maxSize.y; y++) {
					this->map[x].resize(this->maxSize.y, std::vector<Tile*>());
					for (size_t z = 0; z < this->layer; z++) {
						this->map[x][y].resize(this->layer, nullptr);
					}
				}
			}
			while (loadFile >> x >> y >> z >> colliding) {
				std::cout << x << ", " << y << ", " << ", " << z << "\n";
				this->map[maxSize.x][maxSize.y][layer] = new Tile(x, y, gridSize, colliding);
			}
		}
		else {
			std::cout << "Could not loat tile map:" << fileName;
		}
		loadFile.close();
	}
};
ECS_DEFINE_TYPE(TileMap);