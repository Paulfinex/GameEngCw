#pragma once

#include "prefabs_manager.h"
#include "ecm.h"
#include "engine.h"


static int _counter = 0;

static bool treasure_found = false;

void create_new_ghost(sf::Vector2f);

void add_to_counter();

void set_treasure_found(bool);

void set_counter(int counter);