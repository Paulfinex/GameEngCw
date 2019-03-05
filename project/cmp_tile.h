#pragma once

#include <ecm.h>
class TileComponent : public Component {
protected:
	int _health = 2;
public:
	void render() override {}
	void update(float dt) override;
	explicit TileComponent(Entity* p);
	TileComponent() = delete;
	void hitHandler();
	int getHealth();
};