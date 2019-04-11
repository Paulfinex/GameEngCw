#pragma once
#include "ecm.h"
#include "engine.h"

std::shared_ptr<Entity> make_player();
std::shared_ptr<Entity> make_ghost();
void make_walls();
void make_breakable_walls();



