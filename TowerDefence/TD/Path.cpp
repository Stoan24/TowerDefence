#include "pch.h"
#include "Path.h"
#include "utils.h"

Path::Path(std::vector<Vector2f> waypoints)
	:m_Waypoints{ waypoints }
{
	
}

void Path::Draw() const
{
	utils::SetColor(Color4f(0.f, 0.f, 1.f, 1.f));
	for (int i{ 1 }; i < m_Waypoints.size(); i++)
	{
		utils::DrawLine(m_Waypoints[i - 1], m_Waypoints[i]);
	}
}
