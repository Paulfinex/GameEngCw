#include "cmp_treasure.h"
#include <SFML/Graphics.hpp>
#include "cmp_physics.h"
#include "system_physics.h"
#include <LevelSystem.h>
#include "system_resources.h"
#include "engine.h"
#include "cmp_tile.h"

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

		if (_looted)
		{
			_parent->setForDelete();
		}

		for (auto &t : touching)
		{
			auto _player = Engine::GetActiveScene()->ents.find("player");
			if (_parent->isAlive())
			{
				for (auto &b : _player)
				{
					if (t->GetFixtureA() == b->get_components<PhysicsComponent>()[0]->getFixture())
					{
						PlayerLoot();
					}
				}
			}
		}
	}
}

void TreasureComponent::Spawn()
{
}

void TreasureComponent::PlayerLoot()
{
	_looted = true;
}

