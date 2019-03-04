#pragma once

#include <ecm.h>

class ActorMovementComponent : public Component {
protected:
	bool validMove(const sf::Vector2f&);
	float _speed;

public:
	explicit ActorMovementComponent(Entity* p);
	ActorMovementComponent() = delete;

	float getSpeed() const;
	void setSpeed(float _speed);

	void ActorMovementComponent::move(const sf::Vector2f& p);
	void move(float x, float y);

	void render() override {}
	void update(float dt) override;
};