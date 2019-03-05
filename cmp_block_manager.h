#pragma once
#include <ecm.h>
#include <map>
#include <levelsystem.h>


class BlockManager : public Component {
public:
	BlockManager() = delete;
	explicit BlockManager(Entity *p);
	void update(float dt) override;
	void render() override;
	std::map<sf::Vector2f, ls::TILE> BreakableBlocks() { return brekableBlocks; }
protected:
	std::map<sf::Vector2f, ls::TILE> brekableBlocks;
};