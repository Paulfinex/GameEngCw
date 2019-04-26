#include "cmp_pickaxe.h"
#include "cmp_physics.h"
#include "cmp_sprite.h"
#include "system_physics.h"
#include "engine.h"
#include "cmp_tile.h"

using namespace std;
using namespace sf;

void PickAxeComponent::update(double dt)
{
	_parent->GetCompatibleComponent<PhysicsComponent>()[0]->getBody()->SetAwake(true);

	_deleteTime -= dt;
	if (_deleteTime <= 0.f) {
		_parent->setForDelete();
	}

	_player = Engine::GetActiveScene()->ents.find("player")[0];
	auto touching = _parent->get_components<PhysicsComponent>()[0]->getTouching();
	auto blocksToDamage = Engine::GetActiveScene()->ents.find("breakable");

	if (touching.size() > 0)
	{
		for (auto t : touching)
		{
			if (t->GetFixtureA() != _player->get_components<PhysicsComponent>()[0]->getFixture())
			{
				if(t->GetFixtureA() != _player->get_components<PhysicsComponent>()[0]->getFixture())
				_parent->setForDelete();
			}
			else
			{
				_parent->GetCompatibleComponent<PhysicsComponent>()[0]->getBody()->SetAwake(false);
			}


			if (exitLoop) { break; }

			for (auto &b : blocksToDamage)
			{
				if (t->GetFixtureA() == b->GetCompatibleComponent<PhysicsComponent>()[0]->getFixture() ||
					t->GetFixtureB() == b->GetCompatibleComponent<PhysicsComponent>()[0]->getFixture())
				{
					b->GetCompatibleComponent<TileComponent>()[0]->hitHandler();
					_parent->setForDelete();
					exitLoop = true;
				}
			}
		}
	}
}

PickAxeComponent::PickAxeComponent(Entity* p)
	: Component(p)
{
}
