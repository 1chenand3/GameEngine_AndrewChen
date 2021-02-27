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
	defaultColor = sf::Color(color);
	highlightColor = sf::Color(175, 175, 175, 255);
	buttonBG.setSize(size);
	buttonBG.setFillColor(defaultColor);
	buttonBG.setPosition(sf::Vector2f(0, 0));
	buttonText.setCharacterSize(13);
	buttonText.setFillColor(sf::Color::Red);
	buttonText.setPosition(sf::Vector2f(0, 0));
	buttonText.setString(text);
}

Button::~Button()
{
}

bool Button::isHighlighted()
{
	return this->highlighted;
}

void Button::highlight(sf::RenderWindow* window)
{
	highlighted = this->buttonBG.getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window)));
	buttonBG.setFillColor(highlighted ? sf::Color(highlightColor) : sf::Color(defaultColor));
}

void Button::update(sf::Event event, float deltaTime)
{
	checkPressed(event);
}

void Button::render(sf::RenderWindow* window, float deltaTime)
{
	window->draw(buttonBG);
	window->draw(buttonText);
	window->display();
}

void Button::checkPressed(sf::Event event)
{
	this->pressed = highlighted && event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left);
	//if () {
	//}
	clicked = pressed;
}
