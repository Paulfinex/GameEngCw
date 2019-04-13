#include "prefabs_manager.h"
#include "levelsystem.h"
#include "components/cmp_sprite.h"
#include "components/cmp_player_movement.h"
#include "components/cmp_enemy_ai.h"
#include "components/cmp_physics.h"
#include "levelsystem.h"
#include "components//cmp_physics.h"
#include "components/cmp_tile.h"
#include "components/cmp_sprite.h"
#include "system_renderer.h"
#include "components/cmp_ghost.h"
#include "components/cmp_pathfind.h"
#include "pathfinder.h"
#include "system_resources.h"
#include "single_player_scene.h"
#include "components/cmp_text.h"

using namespace std;
using namespace sf;

// Create Player
std::shared_ptr<Entity> make_player()
{
	auto player = Engine::GetActiveScene()->makeEntity();
	player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
	player->addTag("player");
	auto s = player->addComponent<SpriteComponent>();
	auto tex = Resources::get<Texture>("tex.png");
	s->setTexture(tex);
	s->getSprite().setTextureRect(sf::IntRect(35, 0, 32, 32));
	s->getSprite().setScale(1.5f, 1.5f);
	s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);
	player->addComponent<PlayerMovementComponent>();
	auto p = player->addComponent<PhysicsComponent>(true, Vector2f(s->getSprite().getLocalBounds().width + 10.f, s->getSprite().getLocalBounds().height + 10.f));
	p->getBody()->SetSleepingAllowed(false);
	p->getBody()->SetFixedRotation(true);

	Engine::GetActiveScene()->ents.list.push_back(player);
	return player;
}

//Create Ghost
std::shared_ptr<Entity> make_ghost()
{
	auto ghost = Engine::GetActiveScene()->makeEntity();
	ghost->setPosition(ls::getTilePosition(ls::findTiles(ls::ENEMY)[0]));
	ghost->addTag("ghost");
	auto s = ghost->addComponent<SpriteComponent>();
	auto tex = Resources::get<Texture>("tex.png");
	s->setTexture(tex);
	s->getSprite().setTextureRect(sf::IntRect(165, 0, 32, 32));
	s->getSprite().setScale(1.5f, 1.5f);
	s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);
	auto g = ghost->addComponent<PhysicsComponent>(false, Vector2f(s->getSprite().getLocalBounds().width,
		s->getSprite().getLocalBounds().height));
	g->getBody()->SetSleepingAllowed(false);
	g->getBody()->SetFixedRotation(true);
	ghost->addComponent<EnemyAIComponent>();
	Engine::GetActiveScene()->ents.list.push_back(ghost);
	return ghost;
}

// Add physics to walls
void make_walls() 
{
	auto walls = ls::findTiles(ls::WALL);

	for (auto w : walls) 
	{
		auto e = Engine::GetActiveScene()->makeEntity();
		e->addTag("wall");
		e->setPosition(ls::getTilePosition(w) + Vector2f(ls::getTileSize() / 2, ls::getTileSize() / 2));
		e->addComponent<PhysicsComponent>(false, Vector2f(ls::getTileSize(), ls::getTileSize()));

		auto s = e->addComponent<SpriteComponent>();
		auto tex = Resources::get<Texture>("tex.png");
		s->setTexture(tex);
		s->getSprite().setTextureRect(sf::IntRect(32 * 9 + 5, 0, 32, 32));
		s->getSprite().setScale(1.875f, 1.875f);
		s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);

		Engine::GetActiveScene()->ents.list.push_back(e);
	}
}

// Add physics and breakable logic to breakable walls
void make_breakable_walls()
{
	auto blocks = ls::findTiles(ls::BREAKABLE);

	for (auto w : blocks)
	{
		auto e = Engine::GetActiveScene()->makeEntity();
		e->addTag("breakable");
		e->setPosition(ls::getTilePosition(w) + Vector2f(ls::getTileSize() / 2, ls::getTileSize() / 2));
		e->addComponent<PhysicsComponent>(false, Vector2f(ls::getTileSize(), ls::getTileSize()));

		auto s = e->addComponent<SpriteComponent>();
		auto tex = Resources::get<Texture>("tex.png");
		s->setTexture(tex);
		s->getSprite().setTextureRect(sf::IntRect(0, 32, 32, 32));
		s->getSprite().setScale(1.875f, 1.875f);
		s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);
		e->addComponent<TileComponent>();
		Engine::GetActiveScene()->ents.list.push_back(e);
	}
}

// Create Buttons
std::shared_ptr<Entity> make_button(string buttonText)
{
	auto button = Engine::GetActiveScene()->makeEntity();

	auto b = button->addComponent<ShapeComponent>();
	b->setShape<RectangleShape>(Vector2f(350.0f, 34.0f));
	b->getShape().setOrigin(b->getShape().getLocalBounds().width / 2, b->getShape().getLocalBounds().height / 2);
	b->getShape().setFillColor(Color(116, 63, 67, 100));

	auto t = button->addComponent<TextComponent>(buttonText);
	t->getText()->setOrigin(350.0f / 2 - 16.0f, t->getText()->getLocalBounds().height / 2 + 6.0f);
	t->getText()->setColor(Color(228, 166, 114, 100));
	//button->addComponent<ButtonComponent>(s, t);

	return button;
}

std::shared_ptr<Entity> make_logo(string file_name)
{
	auto logo = Engine::GetActiveScene()->makeEntity();
	auto l = logo->addComponent<SpriteComponent>();
	auto tex = Resources::get<Texture>(file_name);
	l->setTexture(tex);
	return logo;
}