#pragma once
#include <ecm.h>

class PickupComponent : public Component {
public:
	PickupComponent() = delete;
	explicit PickupComponent(Entity *p);
	void update(float dt) override;
	void render() override;
};