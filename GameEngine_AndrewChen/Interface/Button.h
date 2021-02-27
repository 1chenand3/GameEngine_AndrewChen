#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Button
{
public:
	sf::RectangleShape buttonBG;
	sf::Text buttonText;
	bool pressed, released, clicked, highlighted;
	Button();
	Button(sf::Vector2f size, sf::Color color, std::string text);
	~Button();
	bool isHighlighted();
	void highlight(sf::RenderWindow* window);
	void update(sf::Event event, float deltaTime);
	void render(sf::RenderWindow* window, float deltaTime);
	void checkPressed(sf::Event event);
private:
	sf::Color defaultColor, highlightColor;
};