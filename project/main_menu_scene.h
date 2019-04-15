#pragma once

#include "engine.h"

class MainMenuScene : public Scene {
public:
	MainMenuScene() = default;
	~MainMenuScene() override = default;
	void UnLoad() override;
	void Load() override;

	void Update(const double& dt) override;

private:
	std::shared_ptr<Entity> _buttonSinglePlayer;
	std::shared_ptr<Entity> _buttonMultiPlayer;
	std::shared_ptr<Entity> _buttonOptions;
	std::shared_ptr<Entity> _buttonQuit;
	double _delay;
};