#include "digit.h"
#include "levelsystem.h"
#include "components/cmp_sprite.h"
#include "components/cmp_player_movement.h"
#include "components/cmp_enemy_ai.h"
#include "components/cmp_physics.h"
#include "levelsystem.h"
#include "components//cmp_physics.h"
#include "components/cmp_tile.h"
#include "components/cmp_sprite.h"
#include <map>
#include "system_renderer.h"
#include "engine.h"
#include "components/cmp_ghost.h"
#include "components/cmp_pathfind.h"
#include "pathfinder.h"
#include "system_resources.h"

using namespace std;
using namespace sf;

shared_ptr<Entity> player;
shared_ptr<Entity> ghost;
shared_ptr<PathfindingComponent> ai;

void GameScene::Load() {

	ls::loadLevelFile("res/maps/map1.txt", 40);
	auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40);
	ls::setOffset(Vector2f(0, ho));

	// Create Player
	{
		player = makeEntity();
		player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
		player->addTag("player");
		auto s = player->addComponent<SpriteComponent>();
		auto tex = Resources::get<Texture>("tex.png");
		s->setTexture(tex);
		s->getSprite().setTextureRect(sf::IntRect(32, 0, 32, 32));
		s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);
		player->addComponent<PlayerMovementComponent>();
		auto p = player->addComponent<PhysicsComponent>(true, Vector2f(s->getSprite().getLocalBounds().width, s->getSprite().getLocalBounds().height));
		p->getBody()->SetSleepingAllowed(false);
		p->getBody()->SetFixedRotation(true);
		ents.list.push_back(player);
	}
	//Create Ghost
	{
		ghost = makeEntity();
		ghost->setPosition(ls::getTilePosition(ls::findTiles(ls::ENEMY)[0]));
		ghost->addTag("ghost");
		auto s = ghost->addComponent<SpriteComponent>();
		auto tex = Resources::get<Texture>("tex.png");
		s->setTexture(tex);
		s->getSprite().setTextureRect(sf::IntRect(165, 0, 32, 32));
		s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);
		auto g = ghost->addComponent<PhysicsComponent>(true, Vector2f(s->getSprite().getLocalBounds().width, 
			s->getSprite().getLocalBounds().height));
		g->getBody()->SetSleepingAllowed(false);
		g->getBody()->SetFixedRotation(true);
		ghost->addComponent<EnemyAIComponent>();
		ents.list.push_back(ghost);
	}

	// Add PathFinding
		// New code from here
	{
		auto path = pathFind(sf::Vector2i(1, 1), sf::Vector2i(ls::getWidth() - 2, ls::getHeight() - 2));
		ai = ghost->addComponent<PathfindingComponent>();
		ai->setPath(path);
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

			auto s = e->addComponent<SpriteComponent>();
			auto tex = Resources::get<Texture>("tex.png");
			s->setTexture(tex);
			s->getSprite().setTextureRect(sf::IntRect(32*9+5, 0, 32, 32));
			s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);

			ents.list.push_back(e);
		}

		for (auto w : blocks) 
		{		
			auto e = makeEntity();
			e->addTag("breakable");			
			e->setPosition(ls::getTilePosition(w) + Vector2f(ls::getTileSize() / 2, ls::getTileSize() / 2));
			e->addComponent<PhysicsComponent>(false, Vector2f(ls::getTileSize(), ls::getTileSize()));
			
			auto s = e->addComponent<SpriteComponent>();
			auto tex = Resources::get<Texture>("tex.png");
			s->setTexture(tex);
			s->getSprite().setTextureRect(sf::IntRect(0, 32, 32, 32));
			s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);
			e->addComponent<TileComponent>();
			ents.list.push_back(e);
		}
	}
}

void GameScene::Update(const double& dt) {

	auto g = ghost;

	if (g->GetCompatibleComponent<EnemyAIComponent>()[0]->_state == EnemyAIComponent::CHASING)
	{
		auto char_relative = ghost->getPosition() - ls::getOffset();
		auto char_tile = Vector2i(char_relative / ls::getTileSize());
		auto player_relative = player->getPosition() - ls::getOffset();
		auto player_tile = Vector2i(player_relative / ls::getTileSize());
		auto path = pathFind(char_tile, player_tile);
		ai->setPath(path);
	}
		Scene::Update(dt);
}

void GameScene::Render() {
	ls::render(Engine::GetWindow()); // REMEMBER THIS
	Scene::Render();
}

void GameScene::respawn() {}

void GameScene::UnLoad(){}


