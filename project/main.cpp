#include <SFML/Graphics.hpp>
#include <iostream>
#include "system_renderer.h"
#include "engine.h"
#include "game.h"

using namespace sf;
using namespace std;

MainMenuScene mainMenu;
SinglePlayerScene singlePlayer;
//MultiplayerScene multiPlayer;
OptionScene optionMenu;
//WinScene winScreen;
//GameOver gameOverScreen


int main() {
	Engine::Start(game_width, game_heigth, "DIG IT", &mainMenu);
	return 0;
}