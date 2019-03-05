#pragma once
#include "scene.h"
#include <SFML/Graphics.hpp>
constexpr uint16_t gameWidth = 1000;
constexpr uint16_t gameHeight = 1000;


extern std::shared_ptr<Scene> gameScene;
extern std::shared_ptr<Scene> menuScene;
extern std::shared_ptr<Scene> activeScene;

class MenuScene : public Scene {
private:
	sf::Text text;

public:
	MenuScene() = default;
	void update(float dt) override;
	void render() override;
	void load() override;
};

class GameScene : public Scene {
private:
	sf::Text text;
	sf::Clock scoreClock;
	void respawn();

public:
	GameScene() = default;
	void update(float dt) override;
	void render() override;
	void load() override;
};