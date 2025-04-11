#include "pch.h"
#include "Tower.h"
#include "utils.h"
#include "Enemy.h"
#include "Bullet.h"

Tower::Tower(Vector2f position)
	:m_Size{ 40.f }
	,m_TowerState{ State::Inactive }
	,m_ShootTimer{ 0.f }
	,m_pFocusEnemy{ nullptr }
	,m_Damage{ 5 }
	,m_IsBulletVisible{ false }
	, m_BulletTimer{ 0.f }
{
	m_Position = Rectf(position.x - m_Size / 2, position.y - m_Size / 2, m_Size, m_Size);
	m_Range = Rectf(position.x - m_Size*1.5f, position.y - m_Size*1.5f, m_Size * 3, m_Size * 3);
}

Tower::~Tower()
{
	//delete m_pBullet;
	//m_pBullet = nullptr;

	delete m_pFocusEnemy;
	m_pFocusEnemy = nullptr;
}

void Tower::Draw() const
{
	utils::SetColor(Color4f(0.f, 1.f, 0.f, 1.f));
	if (m_TowerState == State::Active || m_TowerState == State::Shooting)
	{
		utils::FillRect(m_Position);
	}
	else
	{
		utils::DrawRect(m_Position);
	}

	utils::SetColor(Color4f(1.f, 1.f, 0.f, 1.f));

	utils::DrawRect(m_Range);

	if (m_IsBulletVisible && !m_pFocusEnemy->IsDead())
	{
		utils::SetColor(Color4f(1.f, 1.f, 0.f, 1.f));
		utils::DrawLine(Vector2f(m_Position.left + m_Position.width/2, m_Position.bottom + m_Position.height/2), m_pFocusEnemy->GetPosition());
	}
}

void Tower::Buy(Vector2f mousePos)
{
	if (utils::IsPointInRect(mousePos, m_Position))
	{
		switch (m_TowerState)
		{
		case Tower::Inactive:
			m_TowerState = State::Active;
			break;
		case Tower::Active:
			m_TowerState = State::Inactive;
			break;
		case Tower::Shooting:
			m_TowerState = State::Inactive;
			break;

		default:
			break;
		}
	}
}

Rectf Tower::GetRange()
{
	return m_Range;
}


void Tower::SetShooting(Enemy* enemy)
{
	m_TowerState = State::Shooting;
	
	m_pFocusEnemy = enemy;
}

void Tower::SetActive()
{
	if (m_pFocusEnemy == nullptr)
	{
		m_TowerState = State::Active;
	}
	else
	{
		m_pFocusEnemy = nullptr;
	}
}


void Tower::Update(float elapsedSec)
{
	if (m_TowerState == State::Shooting)
	{
		m_ShootTimer += elapsedSec;

		if (m_ShootTimer >= 0.5f)
		{
			m_pFocusEnemy->IsHit(m_Damage);
			m_ShootTimer = 0;

			m_IsBulletVisible = true;
			m_BulletTimer = 0;
		}
		if (m_IsBulletVisible)
		{
			m_BulletTimer += elapsedSec;
		}

		if (m_BulletTimer >= 0.1f)
		{
			m_IsBulletVisible = false;
		}
		
	}
	//m_pBullet->Update(elapsedSec);
}


bool Tower::IsActive()
{
	return m_TowerState == State::Active;
}

bool Tower::IsShooting()
{
	return m_TowerState == State::Shooting;
}

bool Tower::HasEnemy()
{
	return m_pFocusEnemy != nullptr;
}
