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
EnemyAIComponent::EnemyAIComponent(Entity* p):Component(p) {}

void EnemyAIComponent::update(double dt) {


	auto speed = _groundspeed - 50;

	auto getP = Engine::GetActiveScene()->ents.find("player");

	float gTopDistance = sqrt((pow((_parent->getPosition().x - getP[0]->getPosition().x),2))+ pow((_parent->getPosition().y - getP[0]->getPosition().y),2));

	if (gTopDistance < 250)
	{
		Vector2f direction = { (getP[0]->getPosition().x - _parent->getPosition().x),(_parent->getPosition().y - getP[0]->getPosition().y) };
		_parent->get_components<PhysicsComponent>()[0]->setVelocity(Vector2f(normalize(direction) * speed));

	}
	else
	{
		auto touching = _parent->get_components<PhysicsComponent>()[0]->getTouching();

		if (touching.size() > 0)
		{

			for (auto &t : touching)
			{
				auto blocks = Engine::GetActiveScene()->ents.find("wall");
				for (auto &b : blocks)
					if (t->GetFixtureA() == b->GetCompatibleComponent<PhysicsComponent>()[0]->getFixture() ||
						t->GetFixtureB() == b->GetCompatibleComponent<PhysicsComponent>()[0]->getFixture())
					{
						random1 = ((double)rand() / (RAND_MAX)) * 2 - 1;
						random2 = ((double)rand() / (RAND_MAX)) * 2 - 1;
					}
				auto breakables = Engine::GetActiveScene()->ents.find("breakable");
				for (auto &b : breakables)
					if (t->GetFixtureA() == b->GetCompatibleComponent<PhysicsComponent>()[0]->getFixture() ||
						t->GetFixtureB() == b->GetCompatibleComponent<PhysicsComponent>()[0]->getFixture())
					{
						random1 = ((double)rand() / (RAND_MAX)) * 2 - 1;
						random2 = ((double)rand() / (RAND_MAX)) * 2 - 1;
					}
				auto player = Engine::GetActiveScene()->ents.find("player");
				for (auto &p : player)
					if (t->GetFixtureA() == p->GetCompatibleComponent<PhysicsComponent>()[0]->getFixture() ||
						t->GetFixtureB() == p->GetCompatibleComponent<PhysicsComponent>()[0]->getFixture())
					{
						//Player hit
					}

			}
		}
		Vector2f direction = { random1,random2 };
		_parent->get_components<PhysicsComponent>()[0]->setVelocity(Vector2f(normalize(direction) * speed));
	}
//	random_device dev;
//	default_random_engine engine(dev());

}
