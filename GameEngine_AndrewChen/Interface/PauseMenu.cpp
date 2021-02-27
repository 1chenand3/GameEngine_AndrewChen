#include "PauseMenu.h"

PauseMenu::PauseMenu() = default;

PauseMenu::PauseMenu(sf::RenderWindow * window)
{
	States::setPauseState(false);
	initButtons();
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::update(sf::Event event, float deltaTime, sf::RenderWindow * window)
{
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Escape) {
			States::setPauseState(!States::getPauseState());
		}
	}
	ButtonMap::getMap()["Resume"]->update(event, deltaTime);
	ButtonMap::getMap()["Save"]->update(event, deltaTime);
	ButtonMap::getMap()["Load"]->update(event, deltaTime);
	ButtonMap::getMap()["Quit"]->update(event, deltaTime);
	if (ButtonMap::getMap()["Resume"]->clicked) {
		States::setPauseState(false);
		ButtonMap::getMap()["Resume"]->clicked = false;
	}
	if (ButtonMap::getMap()["Quit"]->clicked) {
		quit(window);
		ButtonMap::getMap()["Quit"]->clicked = false;
	}
}

void PauseMenu::render(sf::RenderWindow * window, float deltaTime, sf::Vector2f resumePosition)
{
	sf::Font font;
	font.loadFromFile("../Debug/Fonts/coure.fon");
	sf::Vector2f sizeOffset = sf::Vector2f(ButtonMap::getMap()["Resume"]->buttonBG.getSize().x / 2, ButtonMap::getMap()["Resume"]->buttonBG.getSize().y / 2);
	ButtonMap::getMap()["Resume"]->buttonBG.setPosition(resumePosition + sf::Vector2f(0, -80) - sizeOffset);
	ButtonMap::getMap()["Resume"]->buttonText.setFont(font);
	ButtonMap::getMap()["Resume"]->buttonText.setPosition(ButtonMap::getMap()["Resume"]->buttonBG.getPosition());
	ButtonMap::getMap()["Resume"]->highlight(window);
	ButtonMap::getMap()["Resume"]->render(window,deltaTime);

	ButtonMap::getMap()["Save"]->buttonBG.setPosition(resumePosition + sf::Vector2f(0, -40) - sizeOffset);
	ButtonMap::getMap()["Save"]->buttonText.setFont(font);
	ButtonMap::getMap()["Save"]->buttonText.setPosition(ButtonMap::getMap()["Save"]->buttonBG.getPosition());
	ButtonMap::getMap()["Save"]->highlight(window);
	ButtonMap::getMap()["Save"]->render(window, deltaTime);

	ButtonMap::getMap()["Load"]->buttonBG.setPosition(resumePosition + sf::Vector2f(0, 0) - sizeOffset);
	ButtonMap::getMap()["Load"]->buttonText.setFont(font);
	ButtonMap::getMap()["Load"]->buttonText.setPosition(ButtonMap::getMap()["Load"]->buttonBG.getPosition());
	ButtonMap::getMap()["Load"]->highlight(window);
	ButtonMap::getMap()["Load"]->render(window, deltaTime);

	ButtonMap::getMap()["Quit"]->buttonBG.setPosition(resumePosition + sf::Vector2f(0, 40) - sizeOffset);
	ButtonMap::getMap()["Quit"]->buttonText.setFont(font);
	ButtonMap::getMap()["Quit"]->buttonText.setPosition(ButtonMap::getMap()["Quit"]->buttonBG.getPosition());
	ButtonMap::getMap()["Quit"]->highlight(window);
	ButtonMap::getMap()["Quit"]->render(window, deltaTime);

	window->display();
}

void PauseMenu::initButtons()
{
	sf::Vector2f size = sf::Vector2f(125, 30);
	ButtonMap::getMap().insert({
		"Resume", new Button(size, sf::Color(175, 175, 175), "Resume the game")
		});
	ButtonMap::getMap().insert({
	"Save", new Button(size, sf::Color(175, 175, 175), "Save map")
		});
	ButtonMap::getMap().insert({
	"Load", new Button(size, sf::Color(175, 175, 175), "Load map")
		});
	ButtonMap::getMap().insert({
	"Quit", new Button(size, sf::Color(175, 175, 175), "Quit the game")
		});
}

void PauseMenu::quit(sf::RenderWindow * window)
{
	window->close();
}
