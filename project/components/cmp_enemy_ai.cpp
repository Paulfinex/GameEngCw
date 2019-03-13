#include "cmp_enemy_ai.h"
#include "levelsystem.h"
#include "cmp_ghost.h"
#include <SFML/Graphics.hpp>
#include "cmp_physics.h"
#include "system_physics.h"
#include <LevelSystem.h>
#include "system_resources.h"
#include "engine.h"
#include "cmp_tile.h"
#include <random>
using namespace sf;
using namespace std;
float random1 = ((double)rand() / (RAND_MAX)) * 2 - 1;
float random2 = ((double)rand() / (RAND_MAX)) * 2 - 1;
static const Vector2i directions[] = { { 1, 0 },{ 0, 1 },{ 0, -1 },{ -1, 0 } };

EnemyAIComponent::EnemyAIComponent(Entity* p) :Component(p) {
	_state = DORMANT;

}

void EnemyAIComponent::update(double dt) {

	auto speed = _groundspeed - 50;
	auto getP = Engine::GetActiveScene()->ents.find("player");

	float gTopDistance = length(_parent->getPosition() - getP[0]->getPosition());

	if (gTopDistance < 150)
	{
		_state = CHASING;

		ChasePlayer(getP, speed);

		auto s = _parent->GetCompatibleComponent<SpriteComponent>()[0];

		if (gTopDistance > 40)
		{
			s->getSprite().setTextureRect(sf::IntRect((32 * 6) + 5, 0, 32, 32));
		}
		else
		{
			s->getSprite().setTextureRect(sf::IntRect((32 * 8) + 5, 0, 32, 32));
		}
	}
	else
	{
		_state = DORMANT;
		Vector2f direction = { 0.f,0.f };
		_parent->GetCompatibleComponent<PhysicsComponent>()[0]->setVelocity(Vector2f(normalize(direction) * speed));
		_parent->GetCompatibleComponent<SpriteComponent>()[0]->getSprite().setTextureRect(sf::IntRect((32 * 5) + 5, 0, 32, 32));
		_parent->GetCompatibleComponent<SpriteComponent>()[0]->getSprite().setOrigin(_parent->GetCompatibleComponent<SpriteComponent>()[0]->getSprite().getLocalBounds().width / 2,
			_parent->GetCompatibleComponent<SpriteComponent>()[0]->getSprite().getLocalBounds().height / 2);
	}

	/*if (_state == CHASING)
	{
		auto touching = _parent->get_components<PhysicsComponent>()[0]->getTouching();


		if (touching.size() > 0)
		{
				
				/*auto blocks = Engine::GetActiveScene()->ents.find("wall");
				for (auto &b : blocks)
				{

					if (t->GetFixtureB() == b->GetCompatibleComponent<PhysicsComponent>()[0]->getFixture())
					{
						random1 = ((double)rand() / (RAND_MAX)) * 2 - 1;
						random2 = ((double)rand() / (RAND_MAX)) * 2 - 1;
					}
				}
				auto breakables = Engine::GetActiveScene()->ents.find("breakable");
				for (auto &b : breakables)
				{
					if (t->GetFixtureB() == b->GetCompatibleComponent<PhysicsComponent>()[0]->getFixture())
					{
						random1 = ((double)rand() / (RAND_MAX)) * 2 - 1;
						random2 = ((double)rand() / (RAND_MAX)) * 2 - 1;
					}
				}	
			}
		}
		/*Vector2f direction = { random1,random2 };
		_parent->get_components<PhysicsComponent>()[0]->setVelocity(Vector2f(normalize(direction) * speed));

		random_device dev;
		default_random_engine engine(dev());
	}*/
}



void EnemyAIComponent::ChasePlayer(std::vector<std::shared_ptr<Entity>> &getP, float speed)
{
	Vector2f direction = { (getP[0]->getPosition().x - _parent->getPosition().x),(_parent->getPosition().y - getP[0]->getPosition().y) };
	_parent->get_components<PhysicsComponent>()[0]->setVelocity(Vector2f(normalize(direction) * speed));
}


