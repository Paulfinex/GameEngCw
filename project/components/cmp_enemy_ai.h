#pragma once

#include <ecm.h>

class EnemyAIComponent : public Component {
private:
	float _groundspeed = 100;
	sf::Vector2f _direction;
public:
	enum state { DORMANT, CHASING, KILLING };
	state _state;
	enum facing { LEFT, RIGHT, UP, DOWN };
	facing _facing;
	explicit EnemyAIComponent(Entity* p);
	EnemyAIComponent() = delete;
	void render() override {}
    void update(double dt) override;
	state getState();
};