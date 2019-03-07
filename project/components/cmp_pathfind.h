//#pragma once
//#include <ecm.h>
//#include <SFML/Graphics.hpp>
//
//class PathfindComponent : public Component {
//public:
//	explicit PathfindComponent(Entity* p);
//	PathfindComponent() = delete;
//	void render() override {}
//	void update(double dt);
//	Vector2f findPath(Vector2f start, Vector2f destination);
//	
//
//};
//
//struct Node {
//public:
//	bool walkable = false;
//	bool visited = false;
//	float dGlobalGoal; // Distance to goal so far
//	float dLocalGoal; // Distance to goal if we took the alternative path
//	int x;
//	int y;
//	vector<Node*> vecNeighbours; // connection to Neighbours
//	Node *previousNode;
//};