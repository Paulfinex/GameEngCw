#include "cmp_enemy_ai.h"
#include "levelsystem.h"
#include <SFML/Graphics.hpp>
#include "cmp_physics.h"
#include "system_physics.h"
#include <LevelSystem.h>
#include "system_resources.h"
#include "engine.h"
#include "cmp_tile.h"
#include "../game.h"
#include "../sound.h"
using namespace sf;
using namespace std;
extern SoundEffects s;
EnemyAIComponent::EnemyAIComponent(Entity* p) :Component(p) {
	_state = DORMANT;

}

void EnemyAIComponent::update(double dt) 
{
	if (_delayActivation >= 0) { _delayActivation -= dt; }

	if (_delayActivation <= 0)
	{
		auto speed = _groundspeed - 50;
		auto getP = Engine::GetActiveScene()->ents.find("player");

		float gTopDistance = length(_parent->getPosition() - getP[0]->getPosition());

		if (gTopDistance < 250.f)
		{
			if (soundCheck)
			{
				s.play_chasing();
				soundCheck = false;
			}
			_state = CHASING;
			
			auto s = _parent->GetCompatibleComponent<SpriteComponent>()[0];

			if (gTopDistance > 100.f)
			{
				s->getSprite().setTextureRect(sf::IntRect((32 * 6) + 5, 0, 32, 32));
			}
			else if (gTopDistance > 70.f && gTopDistance < 100.f)
			{
				s->getSprite().setTextureRect(sf::IntRect((32 * 8) + 5, 0, 32, 32));
			}
			else if (gTopDistance <= 40.f)
			{
				_state = KILLING;
			}
		}
		else
		{
			_state = DORMANT;
			if (!soundCheck)
			{
				s.stop_chasing();
			}
			soundCheck = true;
			Vector2f direction = { 0.f,0.f };
			_parent->GetCompatibleComponent<PhysicsComponent>()[0]->setVelocity(Vector2f(normalize(direction) * speed));
			_parent->GetCompatibleComponent<SpriteComponent>()[0]->getSprite().setTextureRect(sf::IntRect((32 * 5) + 5, 0, 32, 32));
			_parent->GetCompatibleComponent<SpriteComponent>()[0]->getSprite().setOrigin(_parent->GetCompatibleComponent<SpriteComponent>()[0]->getSprite().getLocalBounds().width / 2,
				_parent->GetCompatibleComponent<SpriteComponent>()[0]->getSprite().getLocalBounds().height / 2);
		}
	}
}

EnemyAIComponent::state EnemyAIComponent::getState()
{
	return _state;
}

