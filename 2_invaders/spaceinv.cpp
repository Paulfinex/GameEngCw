#include <SFML/Graphics.hpp>
#include <iostream>
#include "ship.h"
#include "spaceinv.h"
#include "bullet.h"

//...

using namespace sf;
using namespace std;
std::vector<Ship *> ships;
Player* player = new Player();
static Vector2f plPos;
const Keyboard::Key controls[3] = {
	Keyboard::A,
	Keyboard::D,
	Keyboard::Space
};

sf::Texture spritesheet;
sf::Sprite invader;
void Load() {
	if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
		cerr << "Failed to load spritesheet!" << std::endl;
	}
	//invader.setTexture(spritesheet);
	for (int r = 0; r < invaders_columns; ++r) {
		auto rect = IntRect(0, 0, 32, 32);
		for (int c = 0; c < invaders_rows; ++c) {
			Vector2f position = { 100 + ((float)r * 40) , 100 + ((float)c * 40) };
			auto inv = new Invader(rect, position);
			inv->speed = 30;
			inv->direction = 1.0f;
			ships.push_back(inv);
		}
	}

	player->speed = 40;
	//ships.push_back(player);
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


	if (Keyboard::isKeyPressed(controls[0])) {
		player->direction = -1.0f;
	}
	if (Keyboard::isKeyPressed(controls[1])) {
		player->direction = 1.0f;
	}
	if (Keyboard::isKeyPressed(controls[2])) {
		Bullet::Fire(player->getPosition(), false);
	}

	player->Update(dt);
	player->direction = 0.0f;
	for (auto &s : ships) {
		s->Update(dt);
	};
	Bullet::Update(dt);

}

void Render(RenderWindow &window) {
	// Draw Everything
   // window.draw(invader);
	//window.draw(player);
	for (const auto s : ships) {
		window.draw(*s);
	}
	window.draw(*player);
	Bullet::Render(window);
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "Space Invaders");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		//bullet->Render(window);
		window.display();
	}
	return 0;
}
