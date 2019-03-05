#pragma once

#include <SFML\Graphics.hpp>

namespace Renderer {
	void initialise(sf::RenderWindow &);
	sf::RenderWindow &getWindow();

	void shutdown();
	void update(const float &);
	void queue(const sf::Drawable *s);
	void render();
}