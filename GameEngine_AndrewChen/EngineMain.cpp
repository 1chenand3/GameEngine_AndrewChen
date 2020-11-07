#include <SFML/Graphics.hpp>
int main(int argc, char* args[]) {
	int width = 800, height = 600;
	//String title = "Game";
	sf::RenderWindow window(sf::VideoMode(width, height),"Game");
	return width + height;
}
int reInt(int i, int i2) {
	return i + i2;
}