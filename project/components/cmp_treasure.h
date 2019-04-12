#pragma once

#include <ecm.h>
#include <SFML/Graphics.hpp>

class TreasureComponent : public Component {
public:
	explicit TreasureComponent(Entity* t);
	TreasureComponent() = delete;
	bool _looted = false;
	void render() override {}
	void update(double dt);
	void TreasureComponent::Spawn();
	void TreasureComponent::PlayerLoot();
};