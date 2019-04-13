// cmp_pathfind.cpp

#include "cmp_pathfind.h"
#include "levelsystem.h"
#include <SFML/Graphics.hpp>
#include "cmp_physics.h"
#include "system_physics.h"
#include <LevelSystem.h>
#include "system_resources.h"
#include "engine.h"
using namespace sf;
using namespace std;
void PathfindingComponent::update(double dt) {
	_elapsed += dt;
	if (_elapsed >= 1.2f) {
		_elapsed = 0.0;
		if (_index < _path.size()) {

			float new_x = 30 + _path[_index].x * ls::getTileSize();
			float new_y = 30 + _path[_index].y * ls::getTileSize();
			
			_parent->get_components<PhysicsComponent>()[0]->teleport(Vector2f(new_x, new_y));

			if (_parent->getPosition() == Vector2f({ new_x,new_y }))
			{
				++_index;
			}
		}
	}
}

PathfindingComponent::PathfindingComponent(Entity* p) : Component(p) {}

void PathfindingComponent::setPath(std::vector<sf::Vector2i>& path) {
	_index = 0;
	_path = path;
}