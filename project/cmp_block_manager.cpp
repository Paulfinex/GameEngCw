#include <ecm.h>
#include <map>
#include <levelsystem.h>
#include "cmp_block_manager.h"

std::vector<sf::Vector2f> BlockManager::brekableBlocks;

std::vector<sf::Vector2f> BlockManager::getBreakableBlocks() {
	return BlockManager::brekableBlocks;
}

void BlockManager::addBreakableBlocks(sf::Vector2f pos) {
	BlockManager::brekableBlocks.push_back(pos);
}

void BlockManager::EraseBlock(sf::Vector2f p)
{
	BlockManager::brekableBlocks.erase(std::remove(BlockManager::brekableBlocks.begin(), BlockManager::brekableBlocks.end(), p), BlockManager::brekableBlocks.end());
}