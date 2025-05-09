#pragma once
#include "vector"

class Path
{
public:

	enum class Edge {
		Top,
		Bottom,
		Left,
		Right
	};


	Path(const Rectf viewport);
	
	void Draw() const;
	
	Vector2f GetNextPosition(int nextPos);

	int GetSize();

	Vector2f GetRandomPointOnEdge(Edge edge);
	
	std::vector<Vector2f> GenerateRandomPath();

	Vector2f GetFirstPosition();

	Edge GetEdge();

private:

	Edge m_Edge;

	Rectf m_ViewPort;

	std::vector<Vector2f> m_Waypoints;
};

