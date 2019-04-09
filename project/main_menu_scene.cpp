#include "main_menu_scene.h"
#include "system_resources.h"
#include <LevelSystem.h>
#include <system_resources.h>
#include "cmp_text.h"
#include <iostream>
#include <SFML/Window/Keyboard.hpp>
#include "engine.h"
#include <SFML/Window/Mouse.hpp>
#include "ecm.h"
#include "components/cmp_sprite.h"
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics.hpp>
#include "game.h"

using namespace std;
using namespace sf;

void MainMenuScene::Load()
{
	float offSet = 45.0f;
	// Load Logo
	make_logo();
	// Button single player scene
	_buttonSinglePlayer =  make_button("Singleplayer Mode");
	_buttonSinglePlayer->setPosition({ (float)Engine::GetWindow().getSize().x / 2,(float)Engine::GetWindow().getSize().y / 2 + offSet});

	_buttonMultiPlayer = make_button("Multiplayer Mode");
	_buttonMultiPlayer->setPosition({ (float)Engine::GetWindow().getSize().x / 2, _buttonSinglePlayer->getPosition().y + offSet });

	 _buttonOptions = make_button("Options");
	 _buttonOptions->setPosition({ (float)Engine::GetWindow().getSize().x / 2,  _buttonMultiPlayer->getPosition().y + offSet });

	_buttonQuit = make_button("Exit Game");
	_buttonQuit->setPosition({ (float)Engine::GetWindow().getSize().x / 2, _buttonOptions->getPosition().y + offSet });

	Engine::GetWindow().setView(Engine::GetWindow().getDefaultView());

	setLoaded(true);

}

void MainMenuScene::Update(const double& dt) 
{
	View view(FloatRect(0, 0, Engine::GetWindow().getSize().x, Engine::GetWindow().getSize().y));
	Engine::GetWindow().setView(view);

	auto mousePos = Engine::GetWindow().mapPixelToCoords(Mouse::getPosition(Engine::GetWindow()));
	
	// Check buttons if selected
	{
		if (ButtonHandling(_buttonSinglePlayer, mousePos))
		{
			Engine::ChangeScene(&singlePlayer);
		}

		IsSelected(_buttonMultiPlayer, mousePos);
		IsSelected(_buttonOptions, mousePos);
		IsSelected(_buttonQuit, mousePos);
	}

	Scene::Update(dt); 
}

shared_ptr<Entity> MainMenuScene::make_button(string buttonText)
{
	auto button = Engine::GetActiveScene()->makeEntity();

	auto b = button->addComponent<ShapeComponent>();
	b->setShape<RectangleShape>(Vector2f(350.0f, 34.0f));
	b->getShape().setOrigin(b->getShape().getLocalBounds().width / 2, b->getShape().getLocalBounds().height / 2);
	b->getShape().setFillColor(Color(116, 63, 67, 100));
	
	auto t = button->addComponent<TextComponent>(buttonText);
	t->getText()->setOrigin(350.0f / 2 - 16.0f, t->getText()->getLocalBounds().height / 2 + 6.0f); 
	t->getText()->setColor(Color(228, 166, 114, 100));
	//button->addComponent<ButtonComponent>(s, t);

	return button;
}

bool MainMenuScene::IsSelected(shared_ptr<Entity> button, Vector2f mousePos)
{
	if (button->get_components<ShapeComponent>()[0]->getShape().getGlobalBounds().contains(mousePos))
	{
		button->get_components<ShapeComponent>()[0]->getShape().setFillColor(Color(116, 80, 67));
		return true;
	}
	else
	{
		button->get_components<ShapeComponent>()[0]->getShape().setFillColor(Color(116, 63, 67, 100));
		return false;
	}
}
bool MainMenuScene::ButtonHandling(shared_ptr<Entity> button, Vector2f mousePos)
{
	return IsSelected(button, mousePos) && Mouse::isButtonPressed(Mouse::Left);
}

shared_ptr<Entity> MainMenuScene::make_logo()
{
	auto logo = Engine::GetActiveScene()->makeEntity();
	auto l = logo->addComponent<SpriteComponent>();
	auto tex = Resources::get<Texture>("main_menu.png");
	l->setTexture(tex);
	return logo;
}