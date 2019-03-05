#include "digit.h"
#include "levelsystem.h"
#include "components/cmp_sprite.h"
#include "components/cmp_actor_movement.h"
#include "components/cmp_player_movement.h"
#include "components/cmp_enemy_ai.h"
#include "levelsystem.h"
//#include "components/cmp_player_physics.h"
#include "components//cmp_physics.h"
#include "components/cmp_tile.h"
#include "cmp_block_manager.h"
#include <map>
#include "system_renderer.h"
#include "engine.h"

using namespace std;
using namespace sf;

shared_ptr<Entity> player;
vector<shared_ptr<Entity>> ghosts;
vector<shared_ptr<Entity>> breakableBlocks; 

void GameScene::Load() {

	ls::loadLevelFile("res/maps/map1.txt", 40.f);
	auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
	ls::setOffset(Vector2f(0, ho));

	// Create Player
	{
		player = makeEntity();
		player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
		auto s = player->addComponent<ShapeComponent>();
		s->setShape<sf::RectangleShape>(Vector2f(10.f, 10.f));
		s->getShape().setFillColor(Color::Magenta);
		s->getShape().setOrigin(5.f, 5.f);
		player->addComponent<PlayerMovementComponent>();
		ents.list.push_back(player);
		//player->addComponent<PlayerPhysicsComponent>(Vector2f(20.f, 30.f));
	}

	// Add physics colliders to level tiles.
	{
		auto walls = ls::findTiles(ls::WALL);
		auto blocks = ls::findTiles(ls::BREAKABLE);

		for (auto w : walls) {
			auto pos = ls::getTilePosition(w);
			pos += Vector2f(20.f, 20.f); //offset to center
			auto e = makeEntity();
			e->setPosition(pos);
		    //e->addComponent<PhysicsComponent>(false, Vector2f(40.f, 40.f));
		}

		for (auto w : blocks) {
			auto pos = ls::getTilePosition(w);
			pos += Vector2f(20.f, 20.f); //offset to center
			auto e = makeEntity();
			auto s = e->addComponent<ShapeComponent>();
			
			e->setPosition(pos);
		   // e->addComponent<PhysicsComponent>(false, Vector2f(40.f, 40.f));
			
			s->setShape<sf::RectangleShape>(Vector2f(40.f, 40.f));
			s->getShape().setFillColor(Color::Green);
			s->getShape().setOrigin({ 20.f, 20.f });

			BlockManager::addBreakableBlocks(pos);
			e->addComponent<TileComponent>();
			//_ents.list.push_back(breakableBlock);
			breakableBlocks.push_back(e);

		}
	}

	respawn();


	//const sf::Color ghost_cols[]{ {208, 62, 25},		// red Blinky
	//							  {219, 133, 28},		// orange Clyde
	//							  {70, 191, 238},		// cyan inky
	//							  {234, 130, 229} };	// pink Pinky

	//for (int i = 0; i < GHOST_COUNT; ++i) {
	//	auto ghost = make_shared<Entity>();
	//	auto s = ghost->addComponent<ShapeComponent>();
	//	s->setShape<sf::CircleShape>(12.f);
	//	s->getShape().setFillColor(ghost_cols[i % 4]);
	//	s->getShape().setOrigin({ 12.f, 12.f });

	//	//ghost->addComponent<EnemyAIComponent>();

	//	_ents.list.push_back(ghost);
	//	ghosts.push_back(ghost);
	//}

}

void GameScene::Update(const double& dt) {
	/*// Return to main menu
	if (Keyboard::isKeyPressed(Keyboard::Tab)) {
		activeScene = menuScene;
	}*/

	//// Reset game when ghost hists pacman
	//for (auto& g : ghosts) {
	//	if (length(g->getPosition() - player->getPosition()) < 30.f) {
	//		respawn();
	//	}
	//}
	int i = 0;
 	if (Keyboard::isKeyPressed(Keyboard::Z))
	{
 		for (auto& block : breakableBlocks)
		{
 			if (length(block->getPosition() - player->getPosition()) < 25.f)
			{
				block->get_components<TileComponent>()[0]->hitHandler();

				if (block->get_components<TileComponent>()[0]->getHealth() == 0)
				{
					block->setForDelete();
					BlockManager::EraseBlock(block->getPosition());					
				}
			}
			i++;
		}
	}
	Scene::Update(dt);
}

void GameScene::Render() {
	ls::render(Engine::GetWindow()); // REMEMBER THIS
	Scene::Render();
}

void GameScene::respawn() {
	/*auto block_spawn = ls::findTiles(ls::BREAKABLE);
	int i = 0;
	for (auto& s : breakableBlocks) {
		s->setPosition(ls::getTilePosition(block_spawn[i]));
		i++;
	}*/

	player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
	player->GetCompatibleComponent<ActorMovementComponent>()[0]->setSpeed(150.f);

	//auto ghost_spawns = ls::findTiles(ls::ENEMY);
	//for (auto& g : ghosts) {
	//	g->setPosition(ls::getTilePosition(ghost_spawns[rand() % GHOST_COUNT]));
	//	g->GetCompatibleComponent<ActorMovementComponent>()[0]->setSpeed(100.f);
	//}
}

void GameScene::UnLoad(){}


