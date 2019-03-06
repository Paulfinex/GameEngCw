#pragma once

#include <ecm.h>
class TileComponent : public Component {
protected:
	int _health = 5;
public:
	void render() override {}
	void update(double dt) override;
	explicit TileComponent(Entity* p);
	TileComponent() = delete;
	void hitHandler();
	int getHealth();
};