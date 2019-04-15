#include "cmp_treasure.h"
#include <SFML/Graphics.hpp>
#include "cmp_physics.h"
#include "system_physics.h"
#include <LevelSystem.h>
#include "system_resources.h"
#include "engine.h"
#include "cmp_tile.h"
#include "cmp_player_movement.h"

using namespace sf;
using namespace std;

TreasureComponent::TreasureComponent(Entity* t)
	: Component(t)
{
}

void TreasureComponent::update(double dt) {

	auto touching = _parent->get_components<PhysicsComponent>()[0]->getTouching();
	
	if (touching.size() > 0)
	{
		auto _players = Engine::GetActiveScene()->ents.find("player");
		for (auto &t : touching)
		{
			for (auto &p : _players)
			{
				if (_parent->isAlive())
				{
					if (t->GetFixtureA() == p->get_components<PhysicsComponent>()[0]->getFixture() ||
						t->GetFixtureB() == p->get_components<PhysicsComponent>()[0]->getFixture())
					{
						if (delay > 0) { delay -= dt; }

						if (delay <= 0)
						{
							PlayerLoot();
							p->get_components<PlayerMovementComponent>()[0]->_setHasTreasure(true);
						}
					}
				}
			} 
		}
		_players.clear();
	}
}

void TreasureComponent::PlayerLoot()
{
	delay = 0.5f;
	_parent->setForDelete();
}

