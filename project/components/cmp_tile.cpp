#include "cmp_tile.h"

void TileComponent::update(double dt)
{
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
	_health--;
}

int TileComponent::getHealth()
{
	return _health;
}

