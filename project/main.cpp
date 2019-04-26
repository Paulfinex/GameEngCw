#include <SFML/Graphics.hpp>
#include <iostream>
#include "system_renderer.h"
#include "engine.h"
#include "game.h"
#include "inputs.h"

using namespace sf;
using namespace std;

MainMenuScene mainMenu;
SinglePlayerScene singlePlayer;
TutorialScene tutorial;
//MultiplayerScene multiPlayer;
OptionScene optionMenu;
VictoryScene winScreen;
GameOverScene gameOverScreen;


int main() {
	Inputs::load_inputs();
	Engine::Start(game_width, game_heigth, "DIG IT", &mainMenu);
	return 0;
}