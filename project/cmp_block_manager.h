#pragma once
#include <ecm.h>
#include <map>
#include <levelsystem.h>

class BlockManager {
public:
	BlockManager() = delete;
	static std::vector<sf::Vector2f> getBreakableBlocks();
	static void addBreakableBlocks(sf::Vector2f);
	static void EraseBlock(sf::Vector2f p);
private:
	static std::vector<sf::Vector2f> brekableBlocks;
};