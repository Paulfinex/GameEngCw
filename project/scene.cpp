#include "scene.h"

using namespace std;
using namespace sf;

void Scene::update(const float dt) {
	_ents.update(dt);
}

void Scene::render() {
	_ents.render();
}