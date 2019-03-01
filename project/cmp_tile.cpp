#include "cmp_tile.h"

void TileComponent::update(float dt)
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

