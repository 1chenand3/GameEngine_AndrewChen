#include "Engine.h"
using namespace std;
int main(int argc, char* args[]) {
	int width = 800, height = 600;
	// Get one instance of singleton 
	Engine& gameEngine = Engine::GetInstance();
	std::string title = "RPG Engine";
	sf::RenderWindow window(sf::VideoMode(width, height), title);
	//pass the window refrence to the engine and start
	gameEngine.Start(&window);
	return 0;
}
int reInt(int i, int i2) {
	return i + i2;
}