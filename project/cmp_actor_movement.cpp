#include "cmp_actor_movement.h"
#include <levelsystem.h>
#include <map>
#include "cmp_block_manager.h"

using namespace sf;

void ActorMovementComponent::update(float dt) {}

ActorMovementComponent::ActorMovementComponent(Entity* p)
	: _speed(100.0f), Component(p) {}

bool ActorMovementComponent::validMove(const sf::Vector2f& pos) {
	auto blocks = BlockManager::getBreakableBlocks();
	bool pass = true;
	if (LevelSystem::getTileAt(pos) != LevelSystem::BREAKABLE)
		pass = true;
  	else if (LevelSystem::getTileAt(pos) == LevelSystem::BREAKABLE)
	{
		if (blocks.size() == 0)
		{
			pass = true;
		}
		else {
			for (auto b : blocks)
			{
				if (length(b - pos) > 25.f)
				{
					pass = false;
				}
			}
		}
	}
	return (LevelSystem::getTileAt(pos) != LevelSystem::WALL && pass);
}

void ActorMovementComponent::move(const sf::Vector2f& p) {

	auto pp = _parent->getPosition() + p;
	if (validMove(pp))
	{
		_parent->setPosition(pp);
	}
}

void ActorMovementComponent::move(float x, float y) {
	move(Vector2f(x, y));
}

float ActorMovementComponent::getSpeed() const { return _speed; }

void ActorMovementComponent::setSpeed(float speed) { _speed = speed; }