#include "pch.h"
#include "Path.h"
#include "utils.h"
#include "set"

Path::Path(Rectf viewport)
	:m_ViewPort{ viewport },
	m_Edge{ }
{
	m_Waypoints = GenerateRandomPath();
}

void Path::Draw() const
{
	utils::SetColor(Color4f(0.f, 0.f, 1.f, 1.f));
	for (int i{ 1 }; i < m_Waypoints.size(); i++)
	{
		utils::DrawLine(m_Waypoints[i - 1], m_Waypoints[i]);
	}


}

Vector2f Path::GetNextPosition(int nextPos)
{
	return m_Waypoints.at(nextPos);
}

int Path::GetSize()
{
	return m_Waypoints.size();
}

Path::Edge Path::GetOppositeEdge(Edge edge)
{
	switch (edge)
	{
	case Edge::Top:
		return Edge::Bottom;

	case Edge::Bottom:
		return Edge::Top;

	case Edge::Left:
		return Edge::Right;

	case Edge::Right:
		return Edge::Left;

	}
	return Edge::Top;
}

Vector2f Path::GetRandomPointOnEdge(Edge edge)
{
	return Vector2f(0, rand() % (int)m_ViewPort.height);
}

std::vector<Vector2f> Path::GenerateRandomPath()
{
	int maxSteps{ 20 };
	int stepSize{ 100 };

	//select edges
	m_Edge = static_cast<Edge>(rand() % 4);
	Edge endEdge = GetOppositeEdge(m_Edge);

	//get a random position on the edge
	Vector2f startPos = GetRandomPointOnEdge(m_Edge);
	Vector2f endPos = GetRandomPointOnEdge(endEdge);

	std::vector<Vector2f> path;

	//std::set<Vector2f> visitedPos;

	std::set<std::pair<int, int>> visitedPos;

	Vector2f currentPos = startPos;

	path.push_back(currentPos);

	visitedPos.insert({ int(currentPos.x / stepSize), int(currentPos.y / stepSize) });

	for (int i{ 0 }; i < maxSteps; i++)
	{
		
		Vector2f nextPos = currentPos;

		//moving closer to end

		if (rand() % 2 == 0)
		{
			if (endPos.x > currentPos.x)
			{
				nextPos.x += stepSize;
			}
			else if (endPos.x < currentPos.x)
			{
				nextPos.x -= stepSize;
			}
			else
			{
				nextPos.x += 0;
			}
		}
		else
		{
			if (endPos.y > currentPos.y)
			{
				nextPos.y += stepSize;
			}
			else if (endPos.y < currentPos.y)
			{
				nextPos.y -= stepSize;
			}
			else
			{
				nextPos.y += 0;
			}
		}

		
		std::pair<int,int> gridPos = std::make_pair( int(nextPos.x / stepSize), int(nextPos.y / stepSize) );

		int counter{ 0 };
		do
		{
			counter++;

			int direction = rand() % 4;

			switch (direction)
			{
			case 0:
				nextPos = Vector2f(currentPos.x + stepSize, currentPos.y);
				break;

			case 1:
				nextPos = Vector2f(currentPos.x - stepSize, currentPos.y);
				break;

			case 2:
				nextPos = Vector2f(currentPos.x, currentPos.y + stepSize);
				break;

			case 3:
				nextPos = Vector2f(currentPos.x, currentPos.y - stepSize);
				break;

			default:
				break;
			}


			gridPos = std::make_pair(int(nextPos.x / stepSize), int(nextPos.y / stepSize));

		} while (visitedPos.count(gridPos) != 0 && counter < 5);


		//clamp 50 from edge

		if (nextPos.x < stepSize)
		{
			nextPos.x = stepSize;
		}
		else if (nextPos.x > m_ViewPort.width - stepSize)
		{
			nextPos.x = m_ViewPort.width - stepSize;
		}
		if (nextPos.y < stepSize)
		{
			nextPos.y = stepSize;
		}
		else if (nextPos.y > m_ViewPort.height - stepSize)
		{
			nextPos.y = m_ViewPort.height - stepSize;
		}


		visitedPos.insert(gridPos);
		path.push_back(nextPos);
		currentPos = nextPos;

		if (std::abs(currentPos.x - endPos.x) < stepSize && std::abs(currentPos.y - endPos.y) < stepSize)
		{
			break;
		}

	}
	path.push_back(endPos);

	return path;
}

Vector2f Path::GetFirstPosition()
{
	return m_Waypoints.at(0);
}

Path::Edge Path::GetEdge()
{
	return m_Edge;
}
