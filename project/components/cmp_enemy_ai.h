#pragma once

#include <ecm.h>

class EnemyAIComponent : public Component {
public:
	sf::Vector2f _direction;
	enum state { DEADEND, ROAMING, ROTATING, ROTATED };
	state _state;
	explicit EnemyAIComponent(Entity* p);
	EnemyAIComponent() = delete;
	void render() override {}
    void update(double dt) override;
	enum facing { LEFT, RIGHT, UP, DOWN };
	facing _facing;
	float _groundspeed = 160.f;
};