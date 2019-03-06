#pragma once

#include <ecm.h>

class EnemyAIComponent : public Component {
protected:
	sf::Vector2f _direction;
	enum state { DEADEND, ROAMING, ROTATING, ROTATED };
	state _state;
public:
	explicit EnemyAIComponent(Entity* p);
	EnemyAIComponent() = delete;
	void render() override {}
	void update(double dt) override;
};