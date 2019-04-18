#include "tutorial_scene.h"
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
extern SoundEffects s;

using namespace std;
using namespace sf;
void TutorialScene::Load()
{
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
		break;
	case 3:
		break;
	case 4:
		break;
	default:
		break;
	}

	Scene::Update(dt);
}




void TutorialScene::phase1()
{
	if (tutorial_move)
	{
		_player.reset();
		_player = tutorial_player();
		_infoText->GetCompatibleComponent<TextComponent>()[0]->SetText("Welcome! This is your character, you can move using directional arrows, try it!");

		tutorial_move = false;
	}

}

void TutorialScene::phase2()
{
}

void TutorialScene::phase3()
{
}

void TutorialScene::phase4()
{
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