#include "system_renderer.h"
#include <queue>

using namespace std;
using namespace sf;

static queue<const Drawable *> sprites;
static RenderWindow *rw;

void Renderer::initialise(sf::RenderWindow &r) { rw = &r; }

sf::RenderWindow &Renderer::getWindow() { return *rw; }

void  Renderer::shutdown() {
	while (!sprites.empty()) {
		sprites.pop();
	}
}

void Renderer::update(const float &) {}

void Renderer::render() {
	if (rw == nullptr) {
		throw("No render window set.");
	}
	while (!sprites.empty()) {
		rw->draw(*sprites.front());
		sprites.pop();
	}
}

void Renderer::queue(const sf::Drawable *s) { sprites.push(s); }

// Whenever we need to render anything we call somehing like
// Render::queue(&text);