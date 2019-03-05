#pragma once
#include <SFML/Graphics.hpp>
#include <engine.h>
constexpr uint16_t gameHeight = 1000;
constexpr uint16_t gameWidth = 1000;


class GameScene : public Scene {
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