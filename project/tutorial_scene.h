#pragma once

#include "engine.h"

class TutorialScene : public Scene {
public:
	TutorialScene() = default;
	~TutorialScene() override = default;
	void Load() override;
	void UnLoad() override;
	void Update(const double& dt) override;

private:
	std::shared_ptr<Entity> _buttonBack;
	float _offSet = 45.0f;
	double _delay;
	double _iteratorDelay;
};