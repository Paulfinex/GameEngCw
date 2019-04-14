#pragma once
#include "cmp_physics.h"
#include <ecm.h>

class PickAxeComponent : public Component {
protected:
	float _deleteTime = 0.2f;
	sf::Vector2f _direction;
	std::shared_ptr<Entity> _player;
	bool exitLoop = false;

public:
	void update(double dt) override;
	void render() override {}
	explicit PickAxeComponent(Entity* p);
	PickAxeComponent() = delete;
};
