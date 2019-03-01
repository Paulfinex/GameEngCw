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
		_facing = LEFT;
		miningDirection = { -25.f,0.f };
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		displacement.x++;
		_facing = RIGHT;
		miningDirection = { 25.f,0.f };
	}
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		displacement.y--;
		_facing = UP;
		miningDirection = { 0.f,25.f };
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		displacement.y++;
		_facing = DOWN;
		miningDirection = { 0.f,-25.f };
	}
	// Normalise displacement
	float l = sqrt(displacement.x * displacement.x + displacement.y * displacement.y);
	if (l != 0) {
		displacement.x = displacement.x / l;
		displacement.y = displacement.y / l;
	}

	move((float)dt * displacement * _speed);

}

sf::Vector2f PlayerMovementComponent::getMiningDirection()
{
	return miningDirection;
}
