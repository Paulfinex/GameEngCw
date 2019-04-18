#include "option_scene.h"
#include "system_resources.h"
#include "components/cmp_text.h"
#include <SFML/Window/Keyboard.hpp>
#include "engine.h"
#include <SFML/Window/Mouse.hpp>
#include "ecm.h"
#include "components/cmp_sprite.h"
#include "game.h"
#include "prefabs_manager.h"
#include "buttons_manager.h"
#include "inputs.h"
#include <string>
#include <locale> 
#include "sound.h"
extern SoundEffects s;

using namespace std;
using namespace sf;

bool iteratorCheck = false;


void OptionScene::Load()
{
	_delay = 0.1f;
	_iteratorDelay = 0.1f;
	_resIndex = 0;

	for (_resIndex = 0; _resIndex < _resolutions.size(); _resIndex++)
	{
		if (_resolutions[_resIndex] == Engine::CurrRes())
		{
			break;
		}
	}

	_resolutions = 
	{
		("1920x1080"),
		("1920x1200"),
		("1680x1050"),
		("1440x900"),
		("1366x768"),
		("1280x800"),
		("800x600"),
		("640x480")
	};

	make_logo("main_menu.png");

	_buttonResolution = make_button("Resolution - " + Engine::CurrRes());
	_buttonResolution->setPosition({ Engine::GetWindow().getView().getSize().x / 2, Engine::GetWindow().getView().getSize().y / 2 + _offSet});

	_buttonWindowedMode = make_button("Windowed Mode");
	_buttonWindowedMode->setPosition({ _buttonResolution->getPosition().x, _buttonResolution->getPosition().y + _offSet });

	_buttonChangeInput = make_button("Controls");
	_buttonChangeInput->setPosition({ _buttonResolution->getPosition().x,  _buttonWindowedMode->getPosition().y + _offSet });

	_buttonVolume = make_button("Volume: " + to_string(volumeLevel));
	_buttonVolume->setPosition({ _buttonResolution->getPosition().x,  _buttonChangeInput->getPosition().y + _offSet });

	_buttonBack = make_button("Back");
	_buttonBack->setPosition({ _buttonResolution->getPosition().x, _buttonVolume->getPosition().y + _offSet });

	_buttonInputUp = make_button("Move Up - UP");
	_buttonInputUp->setPosition({ _buttonChangeInput->getPosition().x + 351.0f,  _buttonChangeInput->getPosition().y });
	_buttonInputUp->setVisible(false);

	_buttonInputDown = make_button("Move Down - DOWN ");
	_buttonInputDown->setPosition({ _buttonInputUp->getPosition().x,  _buttonInputUp->getPosition().y + _offSet });
	_buttonInputDown->setVisible(false);

	_buttonInputLeft = make_button("Move Left - LEFT");
	_buttonInputLeft->setPosition({ _buttonInputUp->getPosition().x,  _buttonInputDown->getPosition().y + _offSet });	
	_buttonInputLeft->setVisible(false);

	_buttonInputRight = make_button("Move Right - RIGHT");
	_buttonInputRight->setPosition({ _buttonInputUp->getPosition().x,  _buttonInputLeft->getPosition().y + _offSet });
	_buttonInputRight->setVisible(false);

	_buttonInputDig = make_button("DIG - Z");
	_buttonInputDig->setPosition({ _buttonInputUp->getPosition().x,  _buttonInputRight->getPosition().y + _offSet });
	_buttonInputDig->setVisible(false);

	_buttonControlsBack = make_button("Back");
	_buttonControlsBack->setPosition({ _buttonInputUp->getPosition().x,  _buttonInputDig->getPosition().y + _offSet });
	_buttonControlsBack->setVisible(false);
	setLoaded(true);
}

void OptionScene::Update(const double& dt)
{
	if (_delay > 0){_delay -= dt;}
	if (_iteratorDelay > 0) { _iteratorDelay -= dt; }

	auto mousePos = Engine::GetWindow().mapPixelToCoords(Mouse::getPosition(Engine::GetWindow()));
	
	if (_delay <= 0)
	{
		_delay = 0.1f;
		
		if (IsSelected(_buttonResolution, mousePos))
		{
			if (_resIndex < _resolutions.size() - 1 && Keyboard::isKeyPressed(Keyboard::Right) && _iteratorDelay <= 0)
			{
				_iteratorDelay = 0.1f;
				_resIndex++;
				_buttonResolution->GetCompatibleComponent<TextComponent>()[0]->SetText("Resolution - " + _resolutions[_resIndex]);
			}
			else if ((_resIndex > 0) && Keyboard::isKeyPressed(Keyboard::Left) && _iteratorDelay <= 0)
			{
				_iteratorDelay = 0.1f;
				_resIndex--;
				_buttonResolution->GetCompatibleComponent<TextComponent>()[0]->SetText("Resolution - " + _resolutions[_resIndex]);
			}

			if (Mouse::isButtonPressed(Mouse::Left))
			{
					Engine::ChangeResolution(_resolutions[_resIndex]);
			}
		}

		if (IsSelected(_buttonVolume, mousePos))
		{
			if (volumeLevel < 100 && Keyboard::isKeyPressed(Keyboard::Right) && _iteratorDelay <= 0)
			{
				_iteratorDelay = 0.1f;
				volumeLevel+=5;
				main_theme_volume += 5;
				_buttonVolume->GetCompatibleComponent<TextComponent>()[0]->SetText("Volume: " +to_string(volumeLevel));
				s.setVolume(volumeLevel);
				s.setVolumeMainTheme(main_theme_volume);
			}
			else if ((volumeLevel > 0) && Keyboard::isKeyPressed(Keyboard::Left) && _iteratorDelay <= 0)
			{
				_iteratorDelay = 0.1f;
				volumeLevel -= 5;
				_buttonVolume->GetCompatibleComponent<TextComponent>()[0]->SetText("Volume: " + to_string(volumeLevel));
				s.setVolume(volumeLevel);

				if (main_theme_volume > 0)
				{
					main_theme_volume -= 5;
				}

				s.setVolumeMainTheme(main_theme_volume);
			}

			if (Mouse::isButtonPressed(Mouse::Left))
			{
				Engine::ChangeResolution(_resolutions[_resIndex]);
			}
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
			if (IsSelected(_buttonInputUp, mousePos))
			{
				for (int i = sf::Keyboard::A; i <= sf::Keyboard::Z; ++i)
				{
					if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i)))
					{
						Keyboard::Key key = static_cast<sf::Keyboard::Key>(i);
						Inputs::SetKeyboardKeyCode("Up", key);
						_buttonInputUp->GetCompatibleComponent<TextComponent>()[0]->SetText("Move Up - " + Engine::lastKeyPressed);
						break;
					}
				}
			}

			if (IsSelected(_buttonInputDown, mousePos))
			{
				for (int i = sf::Keyboard::A; i <= sf::Keyboard::Z; ++i)
				{
					if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i)))
					{
						Keyboard::Key key = static_cast<sf::Keyboard::Key>(i);
						Inputs::SetKeyboardKeyCode("Down", key);
						_buttonInputDown->GetCompatibleComponent<TextComponent>()[0]->SetText("Move Down - " + Engine::lastKeyPressed);
						break;
					}
				}
			}

			if (IsSelected(_buttonInputLeft, mousePos))
			{
				for (int i = sf::Keyboard::A; i <= sf::Keyboard::Z; ++i)
				{
					if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i)))
					{
						Keyboard::Key key = static_cast<sf::Keyboard::Key>(i);
						Inputs::SetKeyboardKeyCode("Left", key);
						_buttonInputLeft->GetCompatibleComponent<TextComponent>()[0]->SetText("Move Left - " + Engine::lastKeyPressed);
						break;
					}
				}
			}

			if (IsSelected(_buttonInputRight, mousePos))
			{
				for (int i = sf::Keyboard::A; i <= sf::Keyboard::Z; ++i)
				{
					if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i)))
					{
						Keyboard::Key key = static_cast<sf::Keyboard::Key>(i);
						Inputs::SetKeyboardKeyCode("Right", key);
						_buttonInputRight->GetCompatibleComponent<TextComponent>()[0]->SetText("Move Right - " + Engine::lastKeyPressed);
						break;
					}
				}
			}

			if (IsSelected(_buttonInputDig, mousePos))
			{
				for (int i = sf::Keyboard::A; i <= sf::Keyboard::Z; ++i)
				{
					if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i)))
					{
						Keyboard::Key key = static_cast<sf::Keyboard::Key>(i);
						Inputs::SetKeyboardKeyCode("Dig", key);
						_buttonInputDig->GetCompatibleComponent<TextComponent>()[0]->SetText("DIG - " + Engine::lastKeyPressed);
						break;
					}
				}
			}
		}

		if (ButtonHandling(_buttonBack, mousePos))
		{
				Engine::ChangeScene(&mainMenu);
		}
	}

	Scene::Update(dt);
}


void OptionScene::UnLoad()
{
	Scene::UnLoad();
}
