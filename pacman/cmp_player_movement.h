#pragma once

#include <ecm.h>
#include "cmp_actor_movement.h"

class PlayerMovementComponent : public ActorMovementComponent {
public:
	explicit PlayerMovementComponent(Entity* p);
	PlayerMovementComponent() = delete;
	void render() override {}
	void update(float dt) override;
};