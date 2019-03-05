#include "cmp_tile.h"

int _health = 2;

void TileComponent::update(double dt)
{

}

TileComponent::TileComponent(Entity * p) :Component(p)
{
}

void TileComponent::hitHandler()
{

	if (_health > 0)
	{
		_health--;
	}
}

int TileComponent::getHealth()
{
	return _health;
}

