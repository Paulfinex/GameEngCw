#include "single_player_scene.h"
#include "levelsystem.h"
#include "components/cmp_sprite.h"
#include "components/cmp_player_movement.h"
#include "components/cmp_enemy_ai.h"
#include "components/cmp_physics.h"
#include "levelsystem.h"
#include "components//cmp_physics.h"
#include "ecm.h"
#include "components/cmp_tile.h"
#include "components/cmp_sprite.h"
#include "system_renderer.h"
#include "engine.h"
#include "components/cmp_pathfind.h"
#include "pathfinder.h"
#include "system_resources.h"
#include "prefabs_manager.h"
#include "game.h"
#include "components/cmp_text.h"
#include <cmath> 
#include "sound.h"
using namespace std;
using namespace sf;

double delay = 0.2f;
extern SoundEffects s;
void SinglePlayerScene::Load() {

	Engine::GetActiveScene()->ents.list.clear();
	Engine::GetWindow().setMouseCursorVisible(false);
	ls::loadLevelFile("res/maps/map1.txt", 60);

	// Create Player
	_player.reset();
	_player = make_player();

	//Create Ghost
	_ghost.reset();
	_ghost = make_ghost(1.2f);

	// Add Physics to Walls
	make_walls();

	// Add physics and tile_component to breakable walls
	make_breakable_walls();

	{
		_buttonTimer = Engine::GetActiveScene()->makeEntity();
		auto b = _buttonTimer->addComponent<ShapeComponent>();
		b->setShape<RectangleShape>(Vector2f(165.0f, 30.0f));
		b->getShape().setOrigin(b->getShape().getLocalBounds().width / 2 + 10.f, b->getShape().getLocalBounds().height / 2 + 10.f);
		b->getShape().setFillColor(Color::White);

		auto t = _buttonTimer->addComponent<TextComponent>(to_string(winTimer));
		t->getText()->setOrigin(b->getShape().getLocalBounds().width / 2 + 10.f, b->getShape().getLocalBounds().height / 2 + 10.f);
		t->getText()->setColor(Color::Black);

		_buttonTimer->setPosition(Vector2f{ 145.0f,40.0f });
	}
	setLoaded(true);
}

void SinglePlayerScene::Update(const double& dt) {

	_buttonTimer->GetCompatibleComponent<TextComponent>()[0]->SetText(to_string(winTimer));
	if (_ghost->GetCompatibleComponent<EnemyAIComponent>()[0]->getState() == EnemyAIComponent::CHASING)
	{
		auto char_relative = (Vector2i)_ghost->getPosition() - Vector2i(ls::getOffset());
		auto char_tile = Vector2i(char_relative / (int)ls::getTileSize());
		auto player_relative = _player->getPosition() - ls::getOffset();
		auto player_tile = Vector2i(player_relative / ls::getTileSize());
		auto path = pathFind(char_tile, player_tile);
		_ghost->GetCompatibleComponent<PathfindingComponent>()[0]->setPath(path);
	}
	else if (_ghost->GetCompatibleComponent<EnemyAIComponent>()[0]->getState() == EnemyAIComponent::KILLING)
	{
		if (delay > 0) { delay -= dt; }

		if (delay <= 0)
		{
			delay = 0.2f;
			_player->GetCompatibleComponent<PlayerMovementComponent>()[0]->_setHasTreasure(false);
			Engine::ChangeScene(&gameOverScreen);
		}
	}

	if (_player->GetCompatibleComponent<PlayerMovementComponent>()[0]->HasTreasure())
	{
		s.play_timer();
		if (winTimer > 0) { winTimer -= dt;}

		if (winTimer <= 0)
		{
			if (delay > 0) { delay -= dt; }

			if (delay <= 0)
			{
				s.stop_timer();
				_player->GetCompatibleComponent<PlayerMovementComponent>()[0]->_setHasTreasure(false);
				Engine::ChangeScene(&winScreen);
			}
		}
	}

	Scene::Update(dt);
}

void SinglePlayerScene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();
}

void SinglePlayerScene::UnLoad()
{
	ls::unload();

	Scene::UnLoad();
}


