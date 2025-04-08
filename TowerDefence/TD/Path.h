#pragma once
#include "vector"

class Path
{
public:
	Path(std::vector<Vector2f> waypoints);
	
	void Draw() const;
	
	

private:

	std::vector<Vector2f> m_Waypoints;

};

