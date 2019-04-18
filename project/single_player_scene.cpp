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
#include "enemy_spawner.h"
#include <random>
#include <cmath>
#include "sound.h"

using namespace std;
using namespace sf;

double delay = 0.2f;
extern SoundEffects s;
bool timerSoundCheck = true;
bool treasureSoundCheck = true;
std::vector<std::shared_ptr<Entity>> SinglePlayerScene::_ghosts;
int index = 0;

void SinglePlayerScene::Load() {
	srand((unsigned)time(0));
	Engine::GetActiveScene()->ents.list.clear();
	Engine::GetWindow().setMouseCursorVisible(false);
	ls::loadLevelFile("res/maps/map1.txt", 60);

	// Create Player
	_player.reset();
	_player = make_player();

	//Create Ghost
	_ghosts.clear();
	_ghosts.push_back(make_ghost(1.2f, ls::getTilePosition(ls::findTiles(ls::ENEMY)[0])));

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

void SinglePlayerScene::AddGhost(Vector2f position)
{
	if (_ghosts.size() <= 5) {
		auto ghost = make_ghost(1.2f, position);
		_ghosts.push_back(ghost);
	}
}

void SinglePlayerScene::Update(const double& dt) {

	_buttonTimer->GetCompatibleComponent<TextComponent>()[0]->SetText(to_string(winTimer));

	for (auto _ghost : _ghosts)
	{
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
			_player->GetCompatibleComponent<PlayerMovementComponent>()[0]->_setHasTreasure(false);
			winTimer = 20.f;
			set_counter(0);
			Engine::ChangeScene(&gameOverScreen);
			break;
		}
	}

	if (_player->GetCompatibleComponent<PlayerMovementComponent>()[0]->HasTreasure())
	{
		if (timerSoundCheck)
		{
			timerSoundCheck = false;
			s.play_timer();
		}
		if (treasureSoundCheck)
		{
			treasureSoundCheck = false;
			s.play_trasure_spawn();
		}

		if (winTimer > 0) { winTimer -= dt;}

		if (_delay > 0) { _delay -= dt; }

		if(_delay <= 0)
		{
			if (_spawnTimer % 2 == 0 && _ghosts.size() <= 10)
			{
				index = rand() % 26;
				_ghosts.push_back(make_ghost(1.2f, ls::getTilePosition(ls::findTiles(ls::FINALSPAWN)[index])
					+ Vector2f(ls::getTileSize() / 2, ls::getTileSize() / 2)));
			}
			_spawnTimer++;
			_delay = 1.0f;
		}

		if (winTimer <= 0)
		{
			s.stop_timer();
			_player->GetCompatibleComponent<PlayerMovementComponent>()[0]->_setHasTreasure(false);
			winTimer = 20.f;
			set_counter(0);
			Engine::ChangeScene(&winScreen);
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
