#include "Button.h"

Button::Button()
{
}

Button::Button(sf::Vector2f size, sf::Color color, std::string text)
{
	pressed = false;
	released = false;
	clicked = false;
	highlighted = false;
	defualtColor = sf::Color(color);
	highlightColor = sf::Color(175, 175, 175, 255);
}

Button::~Button()
{
}

bool Button::isHighlighted()
{
	return highlighted;
}

void Button::isHighlighted(sf::RenderWindow* window)
{
}

void Button::update(sf::Event event, float deltaTime)
{
}

void Button::render(sf::RenderWindow* window, float deltaTime)
{
}

void Button::checkPressed(sf::Event event)
{
}
