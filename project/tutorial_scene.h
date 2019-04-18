#pragma once

#include "engine.h"

class TutorialScene : public Scene {
public:
	TutorialScene() = default;
	~TutorialScene() override = default;
	void Load() override;
	void UnLoad() override;
	void Render();
	void Update(const double& dt) override;

private:
	std::shared_ptr<Entity> _buttonBack;
	std::shared_ptr<Entity> _infoText;
	std::shared_ptr<Entity> _player;
	float _offSet = 45.0f;
	double _delay;
	double _iteratorDelay;
	std::shared_ptr<Entity> tutorial_player();
	bool tutorial_move = true;
	bool tutorial_walls = true;
	bool tutorial_treasure = true;
	bool tutorial_ghost = true;
	int phase = 1;
	void phase1();
	void phase2();
	void phase3();
	void phase4();

};