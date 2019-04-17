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
#include "components/cmp_pathfind.h"
#include "pathfinder.h"
#include "system_resources.h"
#include "single_player_scene.h"
#include "components/cmp_text.h"
#include "components/cmp_pickaxe.h"
#include "components/cmp_treasure.h"

using namespace std;
using namespace sf;

// Create Player
std::shared_ptr<Entity> make_player()
{
	if (Engine::GetActiveScene()->ents.find("player").size() > 0)
	{
		auto player = Engine::GetActiveScene()->ents.find("player")[0];
		return player;
	}
	else
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
		p->getBody()->SetBullet(true);

		Engine::GetActiveScene()->ents.list.push_back(player);
		return player;
	}
}

// Create Player
void make_pickaxe()
{
	Vector2f offset = { 20.f, 20.f };
	auto player = Engine::GetActiveScene()->ents.find("player")[0];
	auto direction = player->GetCompatibleComponent<PlayerMovementComponent>()[0]->getMiningDirection();
	direction.y *= -1;
	auto pos = player->getPosition() + offset * direction;
	auto pickaxe = Engine::GetActiveScene()->makeEntity();
	pickaxe->setPosition(pos);
	pickaxe->addTag("pickaxe");
	auto s = pickaxe->addComponent<SpriteComponent>();
	auto tex = Resources::get<Texture>("pickaxe.png");
	s->setTexture(tex);
	s->getSprite().setScale(1.5f, 1.5f);
	s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);
	auto phys = pickaxe->addComponent<PhysicsComponent>(true, Vector2f(s->getSprite().getLocalBounds().width, s->getSprite().getLocalBounds().height));
	phys->getBody()->SetBullet(true);
	pickaxe->addComponent<PickAxeComponent>();

}

//Create Ghost
std::shared_ptr<Entity> make_ghost(double _delay, sf::Vector2f position)
{
	auto ghost = Engine::GetActiveScene()->makeEntity();
	ghost->setPosition(position);
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
	
	// Add PathFinding
	auto path = pathFind(sf::Vector2i(1, 1), sf::Vector2i(ls::getWidth() - 2, ls::getHeight() - 2));
	ghost->addComponent<PathfindingComponent>(_delay);
	ghost->GetCompatibleComponent<PathfindingComponent>()[0]->setPath(path);
	
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
	bool treasureSet = false;
	int index = 0;
	srand((unsigned)time(0));
	int indexToMatch = rand() % 104;

	for (auto w : blocks)
	{
		index++;
		auto e = Engine::GetActiveScene()->makeEntity();
		e->addTag("breakable");
		e->setPosition(ls::getTilePosition(w) + Vector2f(ls::getTileSize() / 2, ls::getTileSize() / 2));
		e->addComponent<PhysicsComponent>(false, Vector2f(ls::getTileSize(), ls::getTileSize()));

		auto s = e->addComponent<SpriteComponent>();
		auto tex = Resources::get<Texture>("tex.png");
		s->setTexture(tex);
		s->getSprite().setTextureRect(sf::IntRect(0, 0, 32, 32));
		s->getSprite().setScale(1.875f, 1.875f);
		s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);
		e->addComponent<TileComponent>();
		Engine::GetActiveScene()->ents.list.push_back(e);

		if (index == indexToMatch)
		{
			e->GetCompatibleComponent<TileComponent>()[0]->SetTreasure();
			treasureSet = true;
		}
	}
}
// Create Treasure
std::shared_ptr<Entity> make_treasure(Vector2f position)
{
	auto e = Engine::GetActiveScene()->makeEntity();
	e->addTag("treasure");
	e->setPosition(position);
	auto s = e->addComponent<SpriteComponent>();
	auto tex = Resources::get<Texture>("treasure.png");
	s->setTexture(tex);
	s->getSprite().setScale(2.f, 2.f);
	s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);
	e->addComponent<TreasureComponent>();
	auto p = e->addComponent<PhysicsComponent>(true, Vector2f(s->getSprite().getLocalBounds().width + 10.f, s->getSprite().getLocalBounds().height + 10.f));
	Engine::GetActiveScene()->ents.list.push_back(e);
	return e;
}

// Create Buttons
std::shared_ptr<Entity> make_button(string buttonText)
{
	auto button = Engine::GetActiveScene()->makeEntity();

	auto b = button->addComponent<ShapeComponent>();
	b->setShape<RectangleShape>(Vector2f(420.0f, 34.0f));
	b->getShape().setOrigin(b->getShape().getLocalBounds().width / 2, b->getShape().getLocalBounds().height / 2);
	b->getShape().setFillColor(Color(116, 63, 67, 100));

	auto t = button->addComponent<TextComponent>(buttonText);
	t->getText()->setOrigin(420.0f / 2 - 16.0f, t->getText()->getLocalBounds().height / 2 + 6.0f);
	t->getText()->setColor(Color(228, 166, 114, 100));
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