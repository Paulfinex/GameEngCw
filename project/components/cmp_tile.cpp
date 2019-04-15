#include "cmp_tile.h"
#include "engine.h"
#include "cmp_sprite.h"
#include "system_resources.h"
#include "../prefabs_manager.h"
#include "../sound.h"
extern SoundEffects s;
void TileComponent::update(double dt)
{
	if (delayDamage > 0) { delayDamage = -dt; }

    if(_health <= 0)
	{
		if (TileComponent::has_treasure)
		{
			make_treasure(_parent->getPosition());
		}
		has_treasure = false;

		s.play_break_block();
		_parent->setForDelete();
	}
}

void TileComponent::SetTreasure() 
{
	TileComponent::has_treasure = true;
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

	if (_health <= 2.f && _health > 1.f)
	{
		auto tex = Resources::get<sf::Texture>("break.png");
		_parent->GetCompatibleComponent<SpriteComponent>()[0]->setTexture(tex);
		_parent->GetCompatibleComponent<SpriteComponent>()[0]->getSprite().setScale(1.7f, 1.5f);
	}
	if (_health <= 1.f)
	{
		_parent->GetCompatibleComponent<SpriteComponent>()[0]->getSprite().setScale(1.4f, 1.2f);
	}
}

int TileComponent::getHealth()
{
	return _health;
}

