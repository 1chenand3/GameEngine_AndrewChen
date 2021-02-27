#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
static class ButtonMap
{
public: 
	static std::map<std::string, Button*> & getMap();
private :
	static std::map<std::string, Button*> buttons;
};

