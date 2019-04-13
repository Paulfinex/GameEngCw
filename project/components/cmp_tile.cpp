#include "cmp_tile.h"
#include "engine.h"

void TileComponent::update(double dt)
{
	if (delayDamage > 0) { delayDamage = -dt; }

    if(_health <= 0)
	{
		_parent->setForDelete();

	}
}

TileComponent::TileComponent(Entity * p) :Component(p)
{
}

void TileComponent::hitHandler()
{
	if(delayDamage <= 0.f)
	{
		delayDamage = 0.5f;

		_health--;
	}
}

int TileComponent::getHealth()
{
	return _health;
}

