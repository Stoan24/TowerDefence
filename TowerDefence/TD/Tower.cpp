#include "pch.h"
#include "Tower.h"
#include "utils.h"

Tower::Tower(Vector2f position)
	:m_Size{ 40 }
	,m_IsActive{ false }
{
	m_Position = Rectf(position.x - m_Size / 2, position.y - m_Size / 2, m_Size, m_Size);
}

void Tower::Draw() const
{
	utils::SetColor(Color4f(0.f, 1.f, 0.f, 1.f));
	if (m_IsActive)
	{
		utils::FillRect(m_Position);
	}
	else
	{
		utils::DrawRect(m_Position);
	}
}

void Tower::Buy(Vector2f mousePos)
{
	if (utils::IsPointInRect(mousePos, m_Position))
	{
		m_IsActive = !m_IsActive;
	}
}
