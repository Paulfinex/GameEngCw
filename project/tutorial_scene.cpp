#include "tutorial_scene.h"
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
void TutorialScene::Load()
{
	_delay = 0.3f;
	float offSet = 45.0f;

	_buttonBack = make_button("Main Menu");
	_buttonBack->setPosition({  Engine::GetWindow().getView().getSize().x / 8,Engine::GetWindow().getView().getSize().y - Engine::GetWindow().getView().getSize().y/8 });

	setLoaded(true);
}

void TutorialScene::Update(const double & dt)
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
			if (ButtonHandling(_buttonBack, mousePos))
			{
				Engine::ChangeScene(&mainMenu);
			}
		}
	}

	Scene::Update(dt);
}


void TutorialScene::UnLoad()
{

	Scene::UnLoad();
}

