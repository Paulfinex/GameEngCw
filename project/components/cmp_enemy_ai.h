#pragma once

#include <ecm.h>

class EnemyAIComponent : public Component {
public:
	sf::Vector2f _direction;
	enum state { DORMANT, DEADEND, ROAMING, ROTATING, ROTATED, CHASING };
	state _state;
	explicit EnemyAIComponent(Entity* p);
	EnemyAIComponent() = delete;
	void render() override {}
    void update(double dt) override;
	void ChasePlayer(std::vector<std::shared_ptr<Entity>> &getP, float speed);
	enum facing { LEFT, RIGHT, UP, DOWN };
	facing _facing;
	float _groundspeed = 100;
	char getState();
};