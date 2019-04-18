#include "tutorial_scene.h"
#include "levelsystem.h"
#include "system_resources.h"
#include "components/cmp_text.h"
#include <SFML/Window/Keyboard.hpp>
#include "engine.h"
#include <SFML/Window/Mouse.hpp>
#include "ecm.h"
#include "components/cmp_sprite.h"
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics.hpp>
#include "game.h"
#include "prefabs_manager.h"
#include "buttons_manager.h"
#include "sound.h"
#include "components/cmp_player_movement.h"
#include "components/cmp_enemy_ai.h"
#include "components/cmp_physics.h"
#include "components/cmp_tile.h"
#include "components/cmp_treasure.h"
#include "components/cmp_pathfind.h"
#include "pathfinder.h"
extern SoundEffects s;

using namespace std;
using namespace sf;

std::vector<std::shared_ptr<Entity>> TutorialScene::_ghost_list;
bool timerCheck = true;
void TutorialScene::Load()
{

	ls::loadLevelFile("res/maps/map0.txt", 60);
	_delay = 0.3f;
	float offSet = 45.0f;
	_infoText = Engine::GetActiveScene()->makeEntity();
	auto b = _infoText->addComponent<ShapeComponent>();
	b->setShape<RectangleShape>(Vector2f(165.0f, 30.0f));
	b->getShape().setOrigin(b->getShape().getLocalBounds().width / 2 + 10.f, b->getShape().getLocalBounds().height / 2 + 10.f);
	b->getShape().setFillColor(Color::Black);
	auto t = _infoText->addComponent<TextComponent>("");
	t->getText()->setOrigin(b->getShape().getLocalBounds().width / 2 + 10.f, b->getShape().getLocalBounds().height / 2 + 10.f);
	float x = Engine::GetWindow().getView().getSize().x / 9;
	float y = Engine::GetWindow().getView().getSize().y / 9;
	t->getText()->setColor(Color::White);

	_infoText->setPosition(Vector2f{ x,y});


	setLoaded(true);
}

void TutorialScene::Update(const double & dt)
{
	
	switch (phase)
	{
	case 1:
		phase1();
		break;
	case 2:
		phase2();
		break;
	case 3:
		phase3();
		break;
	case 4:
		phase4(dt);
		for (auto _ghost : _ghost_list)
		{
			
				auto char_relative = (Vector2i)_ghost->getPosition() - Vector2i(ls::getOffset());
				auto char_tile = Vector2i(char_relative / (int)ls::getTileSize());
				auto player_relative = _player->getPosition() - ls::getOffset();
				auto player_tile = Vector2i(player_relative / ls::getTileSize());
				auto path = pathFind(char_tile, player_tile);
				_ghost->GetCompatibleComponent<PathfindingComponent>()[0]->setPath(path);
			
			 if (_ghost->GetCompatibleComponent<EnemyAIComponent>()[0]->getState() == EnemyAIComponent::KILLING)
			{
				Engine::ChangeScene(&gameOverScreen);
				break;
			}
		}
		break;
	default:
		break;
	}

	Scene::Update(dt);
}




void TutorialScene::phase1()
{
	if (phase_1)
	{
		_player.reset();
		_player = tutorial_player();
		_infoText->GetCompatibleComponent<TextComponent>()[0]->SetText("Welcome! This is your character, you can move using directional arrows, try it!");

		phase_1 = false;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)|| sf::Keyboard::isKeyPressed(sf::Keyboard::Up)|| sf::Keyboard::isKeyPressed(sf::Keyboard::Left)|| sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		phase++;
	}

}

void TutorialScene::phase2()
{
	if (phase_2)
	{
		_wall = tutorial_wall();
		_breakable = tutorial_breakable();
		_infoText->GetCompatibleComponent<TextComponent>()[0]->SetText("Congratulations! Next, walls! There are two types of wall, but only one is breakable.\n Use the key Z next to them and find which one can be destroyed!");

		phase_2 = false;
	}
	if (_breakable->GetCompatibleComponent<TileComponent>()[0]->getHealth() == 0)
	{
		phase++;
	}
}

void TutorialScene::phase3()
{
	if (phase_3)
	{
		_infoText->GetCompatibleComponent<TextComponent>()[0]->SetText("Good Job! Breakable blocks have a random chance to drop a treasure, loot it and \n keep it safe for 20 seconds to win the level!");
		tutorial_treasure();
		phase_3 = false;
	}
	if (_player->GetCompatibleComponent<PlayerMovementComponent>()[0]->HasTreasure())
	{
		phase++;
	}
}

void TutorialScene::phase4(const double& dt)
{
	if (phase_4)
	{ 
		Vector2f pos = { (_player->getPosition().x -100.f),(_player->getPosition().y-100.f) };
		_ghost_list.push_back(make_ghost(1.2f, pos));
		_infoText->GetCompatibleComponent<TextComponent>()[0]->SetText("A ghost has spawned to protect the treasure! RUN!\n Timer: " + to_string(timer));
		phase_4 = false;
	}
	
	if (timerCheck)
		{
			timerCheck = false;
			s.play_timer();
		}
	if (timer > 0) { timer -= dt; _infoText->GetCompatibleComponent<TextComponent>()[0]->SetText("A ghost has spawned to protect the treasure! RUN!\n Timer: " + to_string(timer));
	}


	
	if (timer <= 0)
	{
		s.stop_timer();
		Engine::ChangeScene(&winScreen);
	}
}


void TutorialScene::UnLoad()
{

	Scene::UnLoad();
}

void TutorialScene::Render()
{
	Scene::Render();
}



std::shared_ptr<Entity> TutorialScene::tutorial_player()
{

	auto player = Engine::GetActiveScene()->makeEntity();
	float x = Engine::GetWindow().getView().getSize().x / 2;
	float y = Engine::GetWindow().getView().getSize().y / 2;
	Vector2f pos = { x,y };
	player->setPosition(pos);
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

std::shared_ptr<Entity> TutorialScene::tutorial_wall()
{
	auto e = Engine::GetActiveScene()->makeEntity();
	e->addTag("wall");
	float x = Engine::GetWindow().getView().getSize().x / 2-250.f;
	float y = Engine::GetWindow().getView().getSize().y / 2;
	Vector2f pos = { x,y };
	e->setPosition(pos);
	e->addComponent<PhysicsComponent>(false, Vector2f(100.f, 100.f));

	auto s = e->addComponent<SpriteComponent>();
	auto tex = Resources::get<Texture>("tex.png");
	s->setTexture(tex);
	s->getSprite().setTextureRect(sf::IntRect(32 * 9 + 5, 0, 32, 32));
	s->getSprite().setScale(1.875f, 1.875f);
	s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);

	Engine::GetActiveScene()->ents.list.push_back(e);
	return e;
}

std::shared_ptr<Entity> TutorialScene::tutorial_breakable()
{
	auto e = Engine::GetActiveScene()->makeEntity();
	e->addTag("breakable");
	float x = Engine::GetWindow().getView().getSize().x / 2 + 250.f;
	float y = Engine::GetWindow().getView().getSize().y / 2;
	Vector2f pos = { x,y };
	e->setPosition(pos);
	e->addComponent<PhysicsComponent>(false, Vector2f(100.f,100.f));

	auto t = e->addComponent<SpriteComponent>();
	auto tex = Resources::get<Texture>("tex.png");
	t->setTexture(tex);
	t->getSprite().setTextureRect(sf::IntRect(0, 0, 32, 32));
	t->getSprite().setScale(1.875f, 1.875f);
	t->getSprite().setOrigin(t->getSprite().getLocalBounds().width / 2, t->getSprite().getLocalBounds().height / 2);
	e->addComponent<TileComponent>();
	Engine::GetActiveScene()->ents.list.push_back(e);
	return e;
}

std::shared_ptr<Entity> TutorialScene::tutorial_treasure()
{
	auto e = Engine::GetActiveScene()->makeEntity();
	e->addTag("treasure");
	float x = Engine::GetWindow().getView().getSize().x / 2 + 250.f;
	float y = Engine::GetWindow().getView().getSize().y / 2;
	Vector2f pos = { x,y };
	e->setPosition(pos);
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
