#pragma once
#include <SFML/Graphics.hpp>
#include <engine.h>

class SinglePlayerScene : public Scene {
private:
	std::shared_ptr<Entity> _player;
	static std::vector<std::shared_ptr<Entity>> _ghosts;
	std::shared_ptr<Entity> _buttonTimer;
	int _spawnTimer = 0;
	double _delay = 0.0f;
public:
	void Update(const double& dt) override;
	void Render() override;
	void Load() override;
	void UnLoad() override;
	double winTimer = 20.f;
	static void SinglePlayerScene::AddGhost(std::shared_ptr<Entity>);
};