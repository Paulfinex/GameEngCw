#pragma once

#include "engine.h"

class MainMenuScene : public Scene {
public:
	MainMenuScene() = default;
	~MainMenuScene() override = default;

	void Load() override;

	void Update(const double& dt) override;

	std::shared_ptr<Entity> make_button(std::string);
	std::shared_ptr<Entity> make_logo();
	bool IsSelected(std::shared_ptr<Entity>, sf::Vector2f);
	bool ButtonHandling(std::shared_ptr<Entity>, sf::Vector2f);

private:
	std::shared_ptr<Entity> _buttonSinglePlayer;
	std::shared_ptr<Entity> _buttonMultiPlayer;
	std::shared_ptr<Entity> _buttonOptions;
	std::shared_ptr<Entity> _buttonQuit;
};