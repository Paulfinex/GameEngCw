#include <SFML/Graphics.hpp>
#include <iostream>
#include "single_player_scene.h"
//#include "multi_player_scene.h"
#include "main_menu_scene.h"
//#include "options_menu_scene.h"
#include "system_renderer.h"
#include "engine.h"
#include "game.h"

using namespace sf;
using namespace std;

MainMenuScene mainMenu;
//OptionsScene mainMenu;
SinglePlayerScene singlePlayer;
//MultiplayerScene multiPlayer;

int main() {
	Engine::Start(game_width, game_heigth, "DIG IT", &mainMenu);
	return 0;
}