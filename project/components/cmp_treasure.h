#pragma once

#include <ecm.h>
#include <SFML/Graphics.hpp>

class TreasureComponent : public Component {
public:
	explicit TreasureComponent(Entity* t);
	TreasureComponent() = delete;
	void render() override {}
	void update(double dt);
	void TreasureComponent::PlayerLoot();
	double delay = 0.5f;
};