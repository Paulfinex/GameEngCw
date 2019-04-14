#include "game_over.h"
#include "system_resources.h"
#include "components/cmp_text.h"
#include <SFML/Window/Keyboard.hpp>
#include "engine.h"
#include <SFML/Window/Mouse.hpp>
#include "ecm.h"
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics.hpp>
#include "game.h"
#include "prefabs_manager.h"
#include "buttons_manager.h"

using namespace std;
using namespace sf;

void GameOverScene::Load()
{
	_delay = 0.3f;
	// Load Logo
	make_logo("game_over.png");

	// Button single player scene
	_buttonRetry = make_button("Retry");
	_buttonRetry->setPosition({ (float)Engine::GetWindow().getSize().x / 2,(float)Engine::GetWindow().getSize().y / 2 + offSet });

	_buttonMainMenu = make_button("Main Menu");
	_buttonMainMenu->setPosition({ (float)Engine::GetWindow().getSize().x / 2, _buttonRetry->getPosition().y + offSet });

	_buttonQuit = make_button("Exit Game");
	_buttonQuit->setPosition({ (float)Engine::GetWindow().getSize().x / 2, _buttonMainMenu->getPosition().y + offSet });

	Engine::GetWindow().setView(Engine::GetWindow().getDefaultView());

	setLoaded(true);
}

void GameOverScene::Update(const double& dt)
{
	if (_delay >= 0)
	{
		_delay -= dt;
	}

	auto mousePos = Engine::GetWindow().mapPixelToCoords(Mouse::getPosition(Engine::GetWindow()));

	if (_delay <= 0)
	{
		_delay = 0.2f;
		// Check buttons if selected
		{
			if (ButtonHandling(_buttonRetry, mousePos))
			{
				Engine::ChangeScene((Scene*)&singlePlayer);
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



