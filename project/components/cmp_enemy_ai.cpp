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

using namespace sf;
using namespace std;

static const Vector2i directions[] = { { 1, 0 },{ 0, 1 },{ 0, -1 },{ -1, 0 } };

EnemyAIComponent::EnemyAIComponent(Entity* p):Component(p) {}

void EnemyAIComponent::update(double dt) {


	auto speed = _groundspeed;

	auto getP = Engine::GetActiveScene()->ents.find("player");
	float angle = atan2(getP[0]->getPosition().y - _parent->getPosition().y, getP[0]->getPosition().x - _parent->getPosition().x);

	sf::Vector2f direction = getP[0]->getPosition() ;



	_parent->get_components<PhysicsComponent>()[0]->setVelocity(Vector2f(normalize(direction * angle) * speed));
}
