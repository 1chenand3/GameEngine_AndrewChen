#include "../GameEngine_AndrewChen/Engine.h"
using namespace std;
int main(int argc, char* args[]) {
	int width = 800, height = 600;
	// Get one instance of singleton 
	Engine& gameEngine = Engine::GetInstance();
	std::string title = "RPG Engine";
	sf::RenderWindow window(sf::VideoMode(width, height), title);
	//Create a world and attach entities
	gameEngine.world = ECS::World::createWorld();

	//Make entity
	ECS::Entity* first;
	ECS::Entity* bg;
	ECS::Entity* tux;
	// add systems to the engine
	gameEngine.addSystem(new RenderSystem());
	gameEngine.addSystem(new AnimationSystem());
	gameEngine.addSystem(new MovementSystem());
	gameEngine.addSystem(new InputSystem(&window));
	// Create and assign some entities

	bg = gameEngine.world->create();
	first = gameEngine.world->create();
	tux = gameEngine.world->create();
	// Assign components

	bg->assign<Transform>(0, 0);
	bg->assign<Sprite2D>("../Debug/Pics/bg.jpg");

	first->assign<Transform>(400, 320);
	first->assign<Sprite2D>("../Debug/Pics/herosheet.png");
	first->assign<Animator>(32, 32, 500.0f, 4, 1);

	tux->assign<Transform>(500, 420);
	tux->assign<Sprite2D>("../Debug/Pics/penguin.png");
	tux->assign<Animator>(56, 72, 500.0f, 3, 9);
	tux->assign<InputControl>();
	tux->get<Animator>()->currRow = 0;

	std::cout << bg->getEntityId() << " is the entity ID" << std::endl;
	std::cout << first->getEntityId() << " is the entity ID" << std::endl;
	std::cout << tux->getEntityId() << " is the entity ID" << std::endl;

	//pass the window refrence to the engine and start
	gameEngine.Start(&window);
	return 0;
}
int reInt(int i, int i2) {
	return i + i2;
}