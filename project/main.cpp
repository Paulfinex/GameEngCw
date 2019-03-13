#include <SFML/Graphics.hpp>
#include <iostream>
#include "digit.h"
#include "system_renderer.h"
#include "engine.h"

using namespace sf;
using namespace std;

GameScene gameScene;

int main() {
	Engine::Start(1280, 720, "DIG IT", &gameScene);
	return 0;
}