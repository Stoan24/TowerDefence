#pragma once
#include "vector"

class Path
{
public:
	Path(std::vector<Vector2f> waypoints);
	
	void Draw() const;
	
	Vector2f GetNextPosition(int nextPos);

	int GetSize();
	

private:

	std::vector<Vector2f> m_Waypoints;

};

