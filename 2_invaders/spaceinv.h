//game.h

#pragma once
#include "ship.h"
#include <SFML/Graphics.hpp>
constexpr uint16_t gameWidth = 800;
constexpr uint16_t gameHeight = 600;
constexpr uint16_t invaders_rows = 5;
constexpr uint16_t invaders_columns = 12;
extern std::vector<Ship *> ships;
extern sf::Texture spritesheet;
extern Player* player;