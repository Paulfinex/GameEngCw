#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"
#include "entity.h"
#include "LevelSystem.h"
#include "game.h"

using namespace sf;
using namespace std;

std::vector<Entity *> entities;
Player* player;

//Player* player = new Player();
//static Vector2f plPos;


void Load() {
	// Load Player
	player = new Player();
	Vector2f temp = { 50.0f, 50.0f };
	player->setPosition(ls::getTilePosition({ 1,1 }) + temp);
	entities.push_back(player);

	// Load Level
	ls::loadLevelFile("res/maps/maze_2.txt", 100.0f);
}


void Update(RenderWindow &window) {
	// Reset clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();
	// check and consume events
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}
	for (auto &e : entities) {
		e->update(dt);
	}


}

void Render(RenderWindow &window) {
	ls::render(window);
	for (auto &e : entities) {
		e->render(window);
	}
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "Maze");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}
