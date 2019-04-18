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
	bool tutorial_move = false;
	bool tutorial_walls = false;
	bool tutorial_treasure = false;
	bool tutorial_ghost = false;
	int phase = 1;
	void phase1();
	bool phase_1 = true;
	void phase2();
	bool phase_2 = true;
	void phase3();
	bool phase_3 = true;
	void phase4();
	bool phase_4 = true;

};