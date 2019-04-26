#pragma once

#include <ecm.h>
#include <SFML/Graphics.hpp>

class PlayerMovementComponent : public Component {
public:
	explicit PlayerMovementComponent(Entity* p);
	PlayerMovementComponent() = delete;
	void render() override {}
	void update(double dt);
	enum facing { LEFT, RIGHT, UP, DOWN };
	facing _facing;
	bool _canMove;
	double miningColdDown;
	float _groundspeed;
	sf::Vector2f miningDirection;
	sf::Vector2f getMiningDirection();
	bool _hasTreasure = false;
	void _setHasTreasure(bool);
	bool PlayerMovementComponent::HasTreasure();
	void PlayerMovementComponent::setCanMove(bool m);
	void PlayerMovementComponent::DigIT();

};