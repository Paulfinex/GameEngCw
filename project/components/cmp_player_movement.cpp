#include "cmp_player_movement.h"
#include <SFML/Graphics.hpp>
#include "cmp_physics.h"
#include "system_physics.h"
#include <LevelSystem.h>
#include "system_resources.h"
#include "engine.h"
#include "cmp_tile.h"

using namespace sf;
using namespace std;

PlayerMovementComponent::PlayerMovementComponent(Entity* p)
	: Component(p) 
{
	_groundspeed = 160.f;
	miningDirection = { 1.0f, 0.0f };
}

void PlayerMovementComponent::update(double dt) {

	auto speed = _groundspeed;
	// Movement

	sf::Vector2f direction = { 0.0f, 0.0f };


	if (Joystick::isConnected(0))
	{
		float x = Joystick::getAxisPosition(0, Joystick::X);
		float y = Joystick::getAxisPosition(0, Joystick::Y);
		direction = normalize(Vector2f(abs(x) > 10.0f ? x : 0, abs(y) > 10.0f ? -y : 0));
	}
	else 
	{
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			direction.x--;
			_facing = LEFT;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			direction.x++;
			_facing = RIGHT;
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			direction.y++;
			_facing = UP;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			direction.y--;
			_facing = DOWN;
		}
	}

	if (direction != Vector2f(0.0, 0.0f))
	{
		miningDirection = direction;
	}

	if (_canMove)
		_parent->get_components<PhysicsComponent>()[0]->setVelocity(Vector2f(normalize(direction) * speed));
	else
		_parent->get_components<PhysicsComponent>()[0]->setVelocity(Vector2f(0.0f, 0.0f));

	if (Keyboard::isKeyPressed(Keyboard::Z) || Joystick::isButtonPressed(0, 0))
	{
		DigIT();
	}
}

sf::Vector2f PlayerMovementComponent::getMiningDirection()
{
	return miningDirection;
}

void PlayerMovementComponent::setCanMove(bool m)
{
	_canMove = m;
}

void PlayerMovementComponent::DigIT()
{
	auto touching = _parent->get_components<PhysicsComponent>()[0]->getTouching();

	if (touching.size() > 0)
	{
		for (auto &t : touching)
		{
			auto blocksToDamage = Engine::GetActiveScene()->ents.find("breakable");
			for(auto &b : blocksToDamage)
			if (t->GetFixtureA() == b->GetCompatibleComponent<PhysicsComponent>()[0]->getFixture() ||
				t->GetFixtureB() == b->GetCompatibleComponent<PhysicsComponent>()[0]->getFixture())
			{
				b->GetCompatibleComponent<TileComponent>()[0]->hitHandler();
			}
		}
	}
}