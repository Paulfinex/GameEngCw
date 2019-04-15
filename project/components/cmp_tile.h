#pragma once

#include <ecm.h>
class TileComponent : public Component {
protected:
	int _health = 3;
	double delayDamage = 0.f;
	bool has_treasure = false;
public:
	void render() override {}
	void update(double dt) override;
	explicit TileComponent(Entity* p);
	TileComponent() = delete;
	void hitHandler();
	int getHealth();
	void SetTreasure();
};