#include <ecm.h>
#include <map>
#include <levelsystem.h>
#include "cmp_block_manager.h"

BlockManager::BlockManager(Entity* p)
	: Component(p) {}

std::map<sf::Vector2f, ls::TILE> BlockManager::BreakableBlocks() { return BlockManager::brekableBlocks; }