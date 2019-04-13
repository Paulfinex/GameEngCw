#pragma once

#include "engine.h"

class GameOverScene : public Scene {
public:
	GameOverScene() = default;
	~GameOverScene() override = default;

	void Load() override;

	void Update(const double& dt) override;

private:
	std::shared_ptr<Entity> _buttonRetry;
	std::shared_ptr<Entity> _buttonMainMenu;
	std::shared_ptr<Entity> _buttonQuit;
	double _delay;
	float offSet = 45.0f;
};