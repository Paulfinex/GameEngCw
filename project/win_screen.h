#pragma once

#include "engine.h"

class VictoryScene : public Scene {
public:
	VictoryScene() = default;
	~VictoryScene() override = default;

	void Load() override;

	void Update(const double& dt) override;

private:
	std::shared_ptr<Entity> _buttonRestart;
	std::shared_ptr<Entity> _buttonMainMenu;
	std::shared_ptr<Entity> _buttonQuit;
	double _delay;
	float offSet = 45.0f;
};