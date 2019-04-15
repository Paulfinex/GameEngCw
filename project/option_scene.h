#pragma once

#include "engine.h"

class OptionScene : public Scene {
public:
	OptionScene() = default;
	~OptionScene() override = default;

	void Load() override;
	void UnLoad() override;

	void Update(const double& dt) override;

private:
	std::shared_ptr<Entity> _buttonResolution;
	std::shared_ptr<Entity> _buttonWindowedMode;
	std::shared_ptr<Entity> _buttonChangeInput;
	std::shared_ptr<Entity> _buttonInputUp;
	std::shared_ptr<Entity> _buttonInputDown;
	std::shared_ptr<Entity> _buttonInputRight;
	std::shared_ptr<Entity> _buttonInputLeft;
	std::shared_ptr<Entity> _buttonInputDig;
	std::shared_ptr<Entity> _buttonBack;
	std::shared_ptr<Entity> _buttonControlsBack;
	std::vector<std::string> _resolutions;
	int _resIndex;
	float _offSet = 45.0f;
	double _delay;
	double _iteratorDelay;
};