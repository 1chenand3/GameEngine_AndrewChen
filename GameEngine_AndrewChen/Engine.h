#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
class Engine
{
public:
	sf::RenderWindow* window;
	static Engine& GetInstance(void);
	void Start(sf::RenderWindow* window);
private:
	bool bQuit;
	Engine(void);
	// Needed to prevent refrece form being changed
	Engine(Engine& copy);	// Hide copy
	Engine(Engine&& other);		// Hide move
	Engine& operator = (Engine& copy);		// Hide assignment

	~Engine(void);
	void Update();
};

