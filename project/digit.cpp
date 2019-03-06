#include "digit.h"
#include "levelsystem.h"
#include "components/cmp_sprite.h"
#include "components/cmp_player_movement.h"
#include "components/cmp_enemy_ai.h"
#include "components/cmp_physics.h"
#include "levelsystem.h"
#include "components//cmp_physics.h"
#include "components/cmp_tile.h"
#include <map>
#include "system_renderer.h"
#include "engine.h"
#include "components/cmp_ghost.h"
using namespace std;
using namespace sf;

shared_ptr<Entity> player;
shared_ptr<Entity> ghost;

void GameScene::Load() {

	ls::loadLevelFile("res/maps/map1.txt", 40.f);
	auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
	ls::setOffset(Vector2f(0, ho));

	// Create Player
	{
		player = makeEntity();
		player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
		player->addTag("player");
		auto s = player->addComponent<ShapeComponent>();
		s->setShape<sf::RectangleShape>(Vector2f(10.f, 10.f));
		s->getShape().setFillColor(Color::Magenta);
		s->getShape().setOrigin(5.f, 5.f);
		player->addComponent<PlayerMovementComponent>();
		auto p = player->addComponent<PhysicsComponent>(true, Vector2f(s->getShape().getLocalBounds().width, s->getShape().getLocalBounds().height));
		p->getBody()->SetSleepingAllowed(false);
		p->getBody()->SetFixedRotation(true);
		ents.list.push_back(player);
	}
	//Create Ghost
	{
		ghost = makeEntity();
		ghost->setPosition(ls::getTilePosition(ls::findTiles(ls::ENEMY)[0]));
		ghost->addTag("ghost");
		auto s = ghost->addComponent<ShapeComponent>();
		s->setShape<sf::CircleShape>(10.f);
		s->getShape().setFillColor(Color::Yellow);
		s->getShape().setOrigin(5.f, 5.f);
		auto g = ghost->addComponent<PhysicsComponent>(true, Vector2f(s->getShape().getLocalBounds().width, s->getShape().getLocalBounds().height));
		g->getBody()->SetSleepingAllowed(false);
		g->getBody()->SetFixedRotation(true);
		ghost->addComponent<EnemyAIComponent>();
		ents.list.push_back(ghost);






	}



	// Add physics colliders to level tiles.
	{
		auto walls = ls::findTiles(ls::WALL);
		auto blocks = ls::findTiles(ls::BREAKABLE);

		for (auto w : walls) {
			auto e = makeEntity();
			e->addTag("wall");
			e->setPosition(ls::getTilePosition(w) + Vector2f(ls::getTileSize() / 2, ls::getTileSize() / 2));
		    e->addComponent<PhysicsComponent>(false, Vector2f(ls::getTileSize(), ls::getTileSize()));
			ents.list.push_back(e);
		}

		for (auto w : blocks) 
		{		
			auto e = makeEntity();
			e->addTag("breakable");
			auto s = e->addComponent<ShapeComponent>();
			
			e->setPosition(ls::getTilePosition(w) + Vector2f(ls::getTileSize() / 2, ls::getTileSize() / 2));
			e->addComponent<PhysicsComponent>(false, Vector2f(ls::getTileSize(), ls::getTileSize()));
			
			s->setShape<sf::RectangleShape>(Vector2f(40.f, 40.f));
			s->getShape().setFillColor(Color::Green);
			s->getShape().setOrigin(Vector2f(ls::getTileSize() / 2, ls::getTileSize() / 2));
			e->addComponent<TileComponent>();
			ents.list.push_back(e);
		}
	}
}

void GameScene::Update(const double& dt) {
	Scene::Update(dt);
}

void GameScene::Render() {
	ls::render(Engine::GetWindow()); // REMEMBER THIS
	Scene::Render();
}

void GameScene::respawn() {}

void GameScene::UnLoad(){}


