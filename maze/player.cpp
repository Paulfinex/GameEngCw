//player.h
#include "player.h"
using namespace sf;
using namespace std;

void Player::update(double dt) {
	//Move in four directions based on keys
	const Keyboard::Key controls[4] = {
	Keyboard::W,
	Keyboard::A,
	Keyboard::S,
	Keyboard::D
	};

	float x = 0.0f;
	float y = 0.0f;
	if (Keyboard::isKeyPressed(controls[0])) {
		y--;
	}
	if (Keyboard::isKeyPressed(controls[1])) {
		x--;
	}
	if (Keyboard::isKeyPressed(controls[2])) {
		y++;
	}
	if (Keyboard::isKeyPressed(controls[3])) {
		x++;
	}
	Vector2f pos = { (float)dt*_speed*x  , (float)dt*_speed*y };
	Vector2f playerSize = { 25.0f, 25.0f };
	Vector2f futurePos = getPosition() + pos;
	Vector2f futureNeg = getPosition() + pos;
	if (validMove(futurePos) && validMove(futureNeg))
	{
		move(pos);
	}
	Entity::update(dt);
}

Player::Player()
    : _speed(200.0f), Entity(make_unique<CircleShape>(25.f)) {
  _shape->setFillColor(Color::Magenta);
  _shape->setOrigin(Vector2f(25.f, 25.f));
}

void Player::render(sf::RenderWindow &window) const {
  window.draw(*_shape);
}


bool Player::validMove(Vector2f pos) {
	return (ls::getTileAt(pos) != ls::WALL);
}

