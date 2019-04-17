#include "enemy_spawner.h"
#include "single_player_scene.h"

void create_new_ghost(sf::Vector2f position)
{
	if (_counter == 5)
	{
		SinglePlayerScene::AddGhost(make_ghost(1.2f, position));
	}
}

void add_to_counter()
{
	_counter++;

	if (_counter > 5)
	{
		_counter = 0;
	}
}

void set_counter(int counter)
{
	_counter = counter;
}

void set_treasure_found(bool found)
{
	treasure_found = found;
}