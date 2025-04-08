#pragma once
class Tower
{
public:
	Tower(Vector2f position);

	void Draw() const;

	void Buy(Vector2f mousePos);


private:

	Rectf m_Position;
	float m_Size;

	bool m_IsActive;
};

