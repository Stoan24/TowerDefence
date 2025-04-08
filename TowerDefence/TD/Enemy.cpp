#include "pch.h"
#include "Enemy.h"
#include "utils.h"

Enemy::Enemy(const Vector2f& position, int size, float speed)
	:m_Position{ position }
	, m_Size{ size }
	, m_NextPosition{ }
	, m_Speed{ speed }
{

}

Enemy::~Enemy()
{

}

void Enemy::Draw() const
{
	utils::SetColor(Color4f(1.f, 0.f, 0.f, 1.f));
	utils::FillEllipse(m_Position, m_Size, m_Size);
}

void Enemy::Update(float elapsedSec, const Vector2f& nextWaypoint)
{
	
	m_NextPosition = nextWaypoint;
	if (m_Position.x == m_NextPosition.x)
	{

	}
	Move(elapsedSec);
}

void Enemy::Move(float elapsedSec)
{
	//get distance between enemy and waypoint
	float distance{ this->GetDistance() };

	//get x and y of the waypoint
	float x{ m_NextPosition.x };
	float y{ m_NextPosition.y };

	float ratio{ (m_Speed / distance) * elapsedSec };

	// look if distance that needs to be travelled is smaller than the speed its travelling
	if (distance < ratio)
	{
		m_Position = m_NextPosition;
	}
	//enemy position += (waypoint position - enemy position) --> direction
	else
	{
		m_Position.x += (x - m_Position.x) * ratio;
		m_Position.y += (y - m_Position.y) * ratio;
	}
}

float Enemy::GetDistance()
{
	return utils::GetDistance(m_Position, m_NextPosition);
}
