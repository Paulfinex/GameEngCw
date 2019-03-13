#pragma once

#include <ecm.h>
#include <SFML/Graphics.hpp>

class GhostMovementComponent : public Component {
public:
	explicit GhostMovementComponent(Entity* p);
	GhostMovementComponent() = delete;
	void render() override {}
	void update(double dt);

};