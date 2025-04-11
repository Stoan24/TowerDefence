#include "pch.h"
#include "Enemy.h"
#include "utils.h"
#include "Path.h"

Enemy::Enemy(const Vector2f& position, int size, float speed, int lifePoints, Path* path)
	:m_Position{ position }
	, m_Size{ size }
	, m_NextPosition{ }
	, m_Speed{ speed }
	, m_MaxLifePoints{ lifePoints }
	, m_LifePoints{ lifePoints }
	, m_Path{ path }
{

}

Enemy::~Enemy()
{

}

void Enemy::Draw() const
{
	if (m_LifePoints <= 0) return;

	utils::SetColor(Color4f(1.f, 0.f, 0.f, 1.f));
	utils::FillEllipse(m_Position, m_Size, m_Size);

	//lifebar
	float size{ m_Size * 2.f };
	Vector2f startPos{ m_Position.x - size/2, m_Position.y + size};
	Vector2f endPos{ startPos.x + size, startPos.y};


	// red bar
	utils::SetColor(Color4f(1.f, 0.f, 0.f, 1.f));
	utils::DrawLine(startPos, endPos);



	// green bar
	utils::SetColor(Color4f(0.f, 1.f, 0.f, 1.f));

	endPos.x = startPos.x + size*((float)m_LifePoints / m_MaxLifePoints);
	utils::DrawLine(startPos, endPos);
	
}

void Enemy::Update(float elapsedSec)
{	
	m_NextPosition = m_Path->GetNextPosition(m_CurrentWaypoint);
	
	if (m_CurrentWaypoint != 0)
	{

		// look if the distance is small enough --> change waypoint
		if (GetDistance() < 0.01f)
		{
			m_CurrentWaypoint = (m_CurrentWaypoint + 1) % m_Path->GetSize();
		}
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

bool Enemy::IsInRange(Rectf towerRange)
{
	return utils::IsPointInRect(m_Position, towerRange);
}

Vector2f Enemy::GetPosition()
{
	return m_Position;
}

void Enemy::IsHit(int damage)
{
	m_LifePoints -= damage;
}

bool Enemy::IsDead()
{
	return m_LifePoints <= 0;
}
