#include "win_screen.h"
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
extern SoundEffects s;
using namespace std;
using namespace sf;

void VictoryScene::Load()
{
	s.stop_all();
	s.play_victory();
	_delay = 0.3f;
	// Load Logo
	make_logo("win_screen.png");

	// Button single player scene
	_buttonRestart = make_button("Restart");
	_buttonRestart->setPosition({ (float)Engine::GetWindow().getSize().x / 2,(float)Engine::GetWindow().getSize().y / 2 + offSet });

	_buttonMainMenu = make_button("Main Menu");
	_buttonMainMenu->setPosition({ _buttonRestart->getPosition().x, _buttonRestart->getPosition().y + offSet });

	_buttonQuit = make_button("Exit Game");
	_buttonQuit->setPosition({ _buttonRestart->getPosition().x, _buttonMainMenu->getPosition().y + offSet });

	setLoaded(true);

}

void VictoryScene::Update(const double& dt)
{
	if (_delay > 0)
	{
		_delay -= dt;
	}

	auto mousePos = Engine::GetWindow().mapPixelToCoords(Mouse::getPosition(Engine::GetWindow()));

	if (_delay <= 0)
	{
		_delay = 0.2f;
		// Check buttons if selected
		{
			if (ButtonHandling(_buttonRestart, mousePos))
			{
				Engine::ChangeScene(&singlePlayer);
			}

			if (ButtonHandling(_buttonMainMenu, mousePos))
			{
				Engine::ChangeScene(&mainMenu);
			}


			if (ButtonHandling(_buttonQuit, mousePos))
			{
				Engine::GetWindow().close();
			}
		}
	}

	Scene::Update(dt);
}




