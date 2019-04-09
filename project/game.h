#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "single_player_scene.h"
//#include "multi_player_scene.h"
#include "main_menu_scene.h"
//#include "options_menu_scene.h"
#include "engine.h"


static uint16_t game_width = 1920;
static uint16_t game_heigth = 1080;

extern MainMenuScene mainMenu;
//extern OptionsScene optionsMenu;
extern SinglePlayerScene singlePlayer;
// externMultiplayerScene multiPlayer;