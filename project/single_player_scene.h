#pragma once
#include <SFML/Graphics.hpp>
#include <engine.h>

class SinglePlayerScene : public Scene {
private:
	sf::Text text;
	sf::Clock scoreClock;
	void respawn();

public:
	void Update(const double& dt) override;
	void Render() override;
	void Load() override;
	void UnLoad() override;
};