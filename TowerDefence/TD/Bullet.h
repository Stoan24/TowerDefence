#pragma once
class Bullet
{
public:
	Bullet(Vector2f position);

	void Draw() const;

	void SetDirection(Vector2f direction);

	void Update(float elapsedSec);

	Circlef GetBounds();

	void Hit();

private:

	Vector2f m_Position;
	Vector2f m_Direction;

	int m_Size;
	float m_Speed;
	int m_Damage;
	bool m_IsAlive;
};