#pragma once
#include <ecm.h>
#include <SFML/Graphics.hpp>


class PathfindingComponent : public Component {
protected:
	std::vector<sf::Vector2i> _path;
	size_t _index = 0;
	double _elapsed = 0.0;

public:
	void update(double) override;
	void render() override {}
	void setPath(std::vector<sf::Vector2i>& path);
	explicit PathfindingComponent(Entity* p);
	PathfindingComponent() = delete;
};