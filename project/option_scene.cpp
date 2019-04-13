#include "option_scene.h"
#include "system_resources.h"
#include <system_resources.h>
#include "components/cmp_text.h"
#include <iostream>
#include <SFML/Window/Keyboard.hpp>
#include "engine.h"
#include <SFML/Window/Mouse.hpp>
#include "ecm.h"
#include "components/cmp_sprite.h"
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics.hpp>
#include "game.h"
#include "prefabs_manager.h"
#include "buttons_manager.h"

using namespace std;
using namespace sf;

void OptionScene::Load()
{
	_delay = 0.1f;

	make_logo("main_menu.png");

	_buttonResolution = make_button("Resolution");
	_buttonResolution->setPosition({ (float)Engine::GetWindow().getSize().x / 2,(float)Engine::GetWindow().getSize().y / 2 + _offSet});

	_buttonWindowedMode = make_button("Windowed Mode");
	_buttonWindowedMode->setPosition({ (float)Engine::GetWindow().getSize().x / 2, _buttonResolution->getPosition().y + _offSet });

	_buttonChangeInput = make_button("Controls");
	_buttonChangeInput->setPosition({ (float)Engine::GetWindow().getSize().x / 2,  _buttonWindowedMode->getPosition().y + _offSet });

	_buttonBack = make_button("Back");
	_buttonBack->setPosition({ (float)Engine::GetWindow().getSize().x / 2, _buttonChangeInput->getPosition().y + _offSet });

	_buttonInputUp = make_button("Move Up");
	_buttonInputUp->setPosition({ _buttonChangeInput->getPosition().x + 351.0f,  _buttonChangeInput->getPosition().y });
	_buttonInputUp->setVisible(false);

	_buttonInputDown = make_button("Move Down");
	_buttonInputDown->setPosition({ _buttonInputUp->getPosition().x,  _buttonInputUp->getPosition().y + _offSet });
	_buttonInputDown->setVisible(false);

	_buttonInputLeft = make_button("Move Left");
	_buttonInputLeft->setPosition({ _buttonInputUp->getPosition().x,  _buttonInputDown->getPosition().y + _offSet });	
	_buttonInputLeft->setVisible(false);

	_buttonInputRight = make_button("Move Right");
	_buttonInputRight->setPosition({ _buttonInputUp->getPosition().x,  _buttonInputLeft->getPosition().y + _offSet });
	_buttonInputRight->setVisible(false);

	_buttonInputDig = make_button("DIG");
	_buttonInputDig->setPosition({ _buttonInputUp->getPosition().x,  _buttonInputRight->getPosition().y + _offSet });
	_buttonInputDig->setVisible(false);

	_buttonControlsBack = make_button("Back");
	_buttonControlsBack->setPosition({ _buttonInputUp->getPosition().x,  _buttonInputDig->getPosition().y + _offSet });
	_buttonControlsBack->setVisible(false);

	Engine::GetWindow().setView(Engine::GetWindow().getDefaultView());

	setLoaded(true);
}

void OptionScene::Update(const double& dt)
{
	if (_delay > 0)
	{
		_delay -= dt;
	}

	auto mousePos = Engine::GetWindow().mapPixelToCoords(Mouse::getPosition(Engine::GetWindow()));
	
	if (_delay <= 0)
	{
		_delay = 0.1f;
		// Check buttons if selected
		{
			if (ButtonHandling(_buttonResolution, mousePos))
			{

			}

			if (ButtonHandling(_buttonWindowedMode, mousePos))
			{
				Engine::setWindowedMode();
			}

			if (ButtonHandling(_buttonChangeInput, mousePos))
			{
				_buttonInputUp->setVisible(true);
				_buttonInputDown->setVisible(true);
				_buttonInputRight->setVisible(true);
				_buttonInputLeft->setVisible(true);
				_buttonInputDig->setVisible(true);
				_buttonControlsBack->setVisible(true);
			}

			if (ButtonHandling(_buttonControlsBack, mousePos))
			{
				_buttonInputUp->setVisible(false);
				_buttonInputDown->setVisible(false);
				_buttonInputRight->setVisible(false);
				_buttonInputLeft->setVisible(false);
				_buttonInputDig->setVisible(false);
				_buttonControlsBack->setVisible(false);
			}

			if (_buttonControlsBack->isVisible())
			{
				if (ButtonHandling(_buttonInputUp, mousePos))
				{

				}

				if (ButtonHandling(_buttonInputDown, mousePos))
				{

				}

				if (ButtonHandling(_buttonInputLeft, mousePos))
				{

				}

				if (ButtonHandling(_buttonInputRight, mousePos))
				{

				}

				if (ButtonHandling(_buttonInputDig, mousePos))
				{

				}
			}

			if (ButtonHandling(_buttonBack, mousePos))
			{
				Engine::ChangeScene(&mainMenu);
			}
		}
	}

	Scene::Update(dt);
}
