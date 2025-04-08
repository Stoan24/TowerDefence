#include "pch.h"
#include "Bullet.h"
#include "utils.h"

Bullet::Bullet(Vector2f position)
	:m_Position{ position }
	,m_Speed{ 100.f }
	,m_Size{ 10 }
{
}

void Bullet::Draw() const
{
	//if (!this->m_IsAlive) return;

	utils::SetColor(Color4f(0.f, 1.f, 0.f, 1.f));
	utils::DrawEllipse(m_Position.x, m_Position.y, 10, 10);
}

void Bullet::SetDirection(Vector2f direction)
{
	m_Direction = direction;
}

void Bullet::Update(float elapsedSec)
{
	//if (!this->m_IsAlive) return;


	m_Position += m_Direction * m_Speed * elapsedSec;
}

Circlef Bullet::GetBounds()
{
	return Circlef(m_Position.x, m_Position.y, 10);
}

void Bullet::Hit()
{
	m_IsAlive = !m_IsAlive;
}
