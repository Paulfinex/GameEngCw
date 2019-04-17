#include "cmp_player_movement.h"
#include <SFML/Graphics.hpp>
#include "cmp_physics.h"
#include "system_physics.h"
#include <LevelSystem.h>
#include "system_resources.h"
#include "engine.h"
#include "cmp_tile.h"
#include "../prefabs_manager.h"
#include "cmp_treasure.h"
#include "../sound.h"
#include "../inputs.h"

using namespace sf;
using namespace std;
extern SoundEffects s;
double clickDelay = 0.f;
PlayerMovementComponent::PlayerMovementComponent(Entity* p)
	: Component(p)
{
	_groundspeed = 160.f;
	miningDirection = { 1.0f, 0.0f };
}

void PlayerMovementComponent::_setHasTreasure(bool hasTreasure)
{
	PlayerMovementComponent::_hasTreasure = hasTreasure;
}

bool PlayerMovementComponent::HasTreasure()
{
	return _hasTreasure;
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
		if (Keyboard::isKeyPressed(Inputs::GetKeyboardKeyCode("Left"))) {
			direction.x--;
			_facing = LEFT;
			miningDirection = { -1.0f, 0.0f };
		}
		if (Keyboard::isKeyPressed(Inputs::GetKeyboardKeyCode("Right"))) {
			direction.x++;
			_facing = RIGHT;
			miningDirection = { 1.0f, 0.0f };
		}
		if (Keyboard::isKeyPressed(Inputs::GetKeyboardKeyCode("Up"))) {
			direction.y++;
			_facing = UP;
			miningDirection = { 0.0f, 1.0f };
		}
		if (Keyboard::isKeyPressed(Inputs::GetKeyboardKeyCode("Down"))) {
			direction.y--;
			_facing = DOWN;
			miningDirection = { 0.0f, -1.0f };
		}
	}

	if (_canMove)
		_parent->get_components<PhysicsComponent>()[0]->setVelocity(Vector2f(normalize(direction) * speed));
	else
		_parent->get_components<PhysicsComponent>()[0]->setVelocity(Vector2f(0.0f, 0.0f));

	if (miningColdDown > 0) { miningColdDown -= dt; }

	if (miningColdDown <= 0)
	{
		if (Keyboard::isKeyPressed(Inputs::GetKeyboardKeyCode("Dig")) || Joystick::isButtonPressed(0, 0))
		{
			DigIT();
		}
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

	s.play_pickaxe_hit();
	make_pickaxe();
	miningColdDown = 0.5f;
}
