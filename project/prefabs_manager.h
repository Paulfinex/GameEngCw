#pragma once
#include "ecm.h"
#include "engine.h"

std::shared_ptr<Entity> make_player();
std::shared_ptr<Entity> make_ghost();
std::shared_ptr<Entity> make_treasure();
void make_walls();
void make_breakable_walls();
std::shared_ptr<Entity> make_button(std::string);
std::shared_ptr<Entity> make_logo();



