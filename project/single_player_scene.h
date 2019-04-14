#pragma once
#include <SFML/Graphics.hpp>
#include <engine.h>

class SinglePlayerScene : public Scene {
private:
	std::shared_ptr<Entity> _player;
	std::shared_ptr<Entity> _ghost;
	std::shared_ptr<Entity> _treasure;

public:
	void Update(const double& dt) override;
	void Render() override;
	void Load() override;
	void UnLoad() override;
};