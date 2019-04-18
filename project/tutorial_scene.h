#pragma once

#include <SFML/Graphics.hpp>
#include <engine.h>

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
	std::shared_ptr<Entity> _ghost;
	static std::vector<std::shared_ptr<Entity>> _ghost_list;
	float _offSet = 45.0f;
	double _delay;
	double _iteratorDelay;
	std::shared_ptr<Entity> tutorial_player();
	void tutorial_wall();
	void tutorial_breakable();
	int phase = 1;
	void phase1();
	bool phase_1 = true;
	void phase2();
	bool phase_2 = true;
	void phase3();
	bool phase_3 = true;
	void phase4(const double& dt);
	bool phase_4 = true;
	float timer = 20.0f;

};