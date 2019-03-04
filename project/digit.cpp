#include "digit.h"
#include "cmp_sprite.h"
#include "levelsystem.h"
#include "cmp_sprite.h"
#include "cmp_actor_movement.h"
#include "cmp_player_movement.h"
#include "cmp_enemy_ai.h"
#include "levelsystem.h"
#include "cmp_tile.h"
#include "cmp_block_manager.h"
#include <map>

using namespace std;
using namespace sf;

shared_ptr<Entity> player;
vector<shared_ptr<Entity>> ghosts;
vector<shared_ptr<Entity>> breakableBlocks; 

void MenuScene::load() {}

void MenuScene::update(float dt) {
	if (Keyboard::isKeyPressed(Keyboard::Tab)) {
		activeScene = gameScene;
	}
	Scene::update(dt);
}

void MenuScene::render() {
	Scene::render();
}

void GameScene::load() {

	ls::loadLevelFile("res/maps/map1.txt", 50.f);
	size_t breakableBlockCount = (ls::findTiles(ls::BREAKABLE)).size();
	Vector2f temp = { 50.0f,50.0f };
	player = make_shared<Entity>();

	auto s = player->addComponent<ShapeComponent>();
	s->setShape<sf::CircleShape>(12.f);
	s->getShape().setFillColor(Color::Red);
	s->getShape().setOrigin({ 12.f, 12.f });

	player->addComponent<PlayerMovementComponent>();
	_ents.list.push_back(player);

	for (int i = 0; i < breakableBlockCount; ++i) {
		auto breakableBlock = make_shared<Entity>();
		auto s = breakableBlock->addComponent<ShapeComponent>();
		s->setShape<sf::RectangleShape>(temp);
		s->getShape().setFillColor(Color::Green);
		s->getShape().setOrigin({ 0.f, 0.f });

		sf::Vector2f pos = ls::getTilePosition(ls::findTiles(ls::BREAKABLE)[i]);
		BlockManager::addBreakableBlocks(pos);
	
		breakableBlock->addComponent<TileComponent>();
		_ents.list.push_back(breakableBlock);
		breakableBlocks.push_back(breakableBlock);
	}

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

	respawn();

}

void GameScene::update(float dt) {
	// Return to main menu
	if (Keyboard::isKeyPressed(Keyboard::Tab)) {
		activeScene = menuScene;
	}

	//// Reset game when ghost hists pacman
	//for (auto& g : ghosts) {
	//	if (length(g->getPosition() - player->getPosition()) < 30.f) {
	//		respawn();
	//	}
	//}

	int i = 0;
 	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
 	for (auto& block : breakableBlocks)
		{
		cout << length(block->getPosition() - (player->getPosition() + player->GetCompatibleComponent<PlayerMovementComponent>()[0]->miningDirection)) << endl;
 			if (length(block->getPosition() - (player->getPosition() + player->GetCompatibleComponent<PlayerMovementComponent>()[0]->miningDirection)) < 25.f)
			{
				block->get_components<TileComponent>()[0]->hitHandler();
				if (block->get_components<TileComponent>()[0]->getHealth() == 0)
				{
					BlockManager::EraseBlock(block->getPosition());
					breakableBlocks.erase(breakableBlocks.begin()+i);
					block->setForDelete();
				}
			}
			i++;
		}
	}
	Scene::update(dt);
}

void GameScene::render() {
	ls::render(Renderer::getWindow()); // REMEMBER THIS
	Scene::render();
}

void GameScene::respawn() {
	Vector2f temp = { 25.0f,25.0f };
	player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]) + temp);
	player->GetCompatibleComponent<ActorMovementComponent>()[0]->setSpeed(150.f);

	auto block_spawn = ls::findTiles(ls::BREAKABLE);
	int i = 0;
	for (auto& s : breakableBlocks) {
		s->setPosition(ls::getTilePosition(block_spawn[i]));
		i++;
	}

	//auto ghost_spawns = ls::findTiles(ls::ENEMY);
	//for (auto& g : ghosts) {
	//	g->setPosition(ls::getTilePosition(ghost_spawns[rand() % GHOST_COUNT]));
	//	g->GetCompatibleComponent<ActorMovementComponent>()[0]->setSpeed(100.f);
	//}

}


