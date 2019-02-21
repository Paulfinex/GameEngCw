#include "cmp_player_movement.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

PlayerMovementComponent::PlayerMovementComponent(Entity* p)
	: ActorMovementComponent(p) {}

void PlayerMovementComponent::update(float dt) {

	// Movement
	sf::Vector2f displacement = { 0.0f, 0.0f };
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		displacement.x--;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		displacement.x++;
	}
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		displacement.y--;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		displacement.y++;
	}
	// Normalise displacement
	float l = sqrt(displacement.x * displacement.x + displacement.y * displacement.y);
	if (l != 0) {
		displacement.x = displacement.x / l;
		displacement.y = displacement.y / l;
	}

	move((float)dt * displacement * _speed);

}