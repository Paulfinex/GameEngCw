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
#include "components/cmp_ghost.h"
#include "components/cmp_pathfind.h"
#include "pathfinder.h"
#include "system_resources.h"
#include "prefabs_manager.h"

using namespace std;
using namespace sf;


void SinglePlayerScene::Load() {

	ls::loadLevelFile("res/maps/map1.txt", 60);
	//auto ho = Engine::getWindowSize().y - (ls::getHeight() * 60);
	//ls::setOffset(Vector2f(0, ho));

	// Create Player
	_player = make_player();

	//Create Ghost
	_ghost = make_ghost();

	// Add PathFinding
	{
		auto path = pathFind(sf::Vector2i(1, 1), sf::Vector2i(ls::getWidth() - 2, ls::getHeight() - 2));
		_ghost->addComponent<PathfindingComponent>();
		_ghost->GetCompatibleComponent<PathfindingComponent>()[0]->setPath(path);
	}

	// Add Physics to Walls
	make_walls();

	// Add physics and tile_component to breakable walls
	make_breakable_walls();
}

void SinglePlayerScene::Update(const double& dt) {

	if (_ghost->GetCompatibleComponent<EnemyAIComponent>()[0]->_state == EnemyAIComponent::CHASING)
	{
		auto char_relative = (Vector2i)_ghost->getPosition() - Vector2i(ls::getOffset());
		auto char_tile = Vector2i(char_relative / (int)ls::getTileSize());
		auto player_relative = _player->getPosition() - ls::getOffset();
		auto player_tile = Vector2i(player_relative / ls::getTileSize());
		auto path = pathFind(char_tile, player_tile);
		_ghost->GetCompatibleComponent<PathfindingComponent>()[0]->setPath(path);
	}
		Scene::Update(dt);
}

void SinglePlayerScene::Render() {
	ls::render(Engine::GetWindow()); // REMEMBER THIS
	Scene::Render();
}

void SinglePlayerScene::respawn() {}

void SinglePlayerScene::UnLoad(){}


