/*#include "player.h"
#include "system_renderer.h"
using namespace sf;
using namespace std;
void Player::update(float dt) {
	// Movement
	sf::Vector2f displacement = { 0.0f, 0.0f };
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		displacement.x --;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		displacement.x ++;
	}
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		displacement.y --;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		displacement.y ++;
	}
	// Normalise displacement
	float l = sqrt(displacement.x * displacement.x + displacement.y * displacement.y);
	if (l != 0) {
		displacement.x = displacement.x / l;
		displacement.y = displacement.y / l;
	}
	move((float)dt * displacement * _speed);
	Entity::update(dt);
}
Player::Player() {}
void Player::render() {}*/