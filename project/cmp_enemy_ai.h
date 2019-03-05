#pragma once

#include <ecm.h>
#include "cmp_actor_movement.h"

class EnemyAIComponent : public ActorMovementComponent {
protected:
	sf::Vector2f _direction;
	enum state { DEADEND, ROAMING, ROTATING, ROTATED };
	state _state;
public:
	explicit EnemyAIComponent(Entity* p);
	EnemyAIComponent() = delete;
	void render() override {}
	void update(float dt) override;
};