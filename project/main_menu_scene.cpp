#include "main_menu_scene.h"
#include "system_resources.h"
#include "components/cmp_text.h"
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
#include "sound.h"
using namespace std;
using namespace sf;
SoundEffects s;

void MainMenuScene::Load()
{
	s.play_groove();
	float offSet = 45.0f;
	_delay = 0.3f;
	// Load Logo
	make_logo("main_menu.png");
	// Button single player scene
	_buttonSinglePlayer =  make_button("Singleplayer");
	_buttonSinglePlayer->setPosition({Engine::GetWindow().getView().getSize().x / 2,Engine::GetWindow().getView().getSize().y / 2 + offSet});
	
	/*
	_buttonMultiPlayer = make_button("Multiplayer - TBA");
	_buttonMultiPlayer->setPosition({ (float)Engine::GetWindow().getSize().x / 2, _buttonSinglePlayer->getPosition().y + offSet });
	*/

	_buttonOptions = make_button("Options");
	_buttonOptions->setPosition({ _buttonSinglePlayer->getPosition().x,  _buttonSinglePlayer->getPosition().y + offSet });

	_buttonQuit = make_button("Exit Game");
	_buttonQuit->setPosition({ _buttonSinglePlayer->getPosition().x, _buttonOptions->getPosition().y + offSet });

	setLoaded(true);
}

void MainMenuScene::Update(const double& dt) 
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
			if (ButtonHandling(_buttonSinglePlayer, mousePos))
			{
				Engine::ChangeScene(&singlePlayer);
			}

			/*// TBA multiplayer //
			if (ButtonHandling(_buttonMultiPlayer, mousePos))
			{
				cout << "Not Available - TBA" << endl;
			}*/

			if (ButtonHandling(_buttonOptions, mousePos))
			{
				Engine::ChangeScene(&optionMenu);
			}

			if (ButtonHandling(_buttonQuit, mousePos))
			{
				Engine::GetWindow().close();
			}
		}
	}

	Scene::Update(dt); 
}
void MainMenuScene::UnLoad()
{
	Scene::UnLoad();
}



