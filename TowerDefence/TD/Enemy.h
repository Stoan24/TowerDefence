#pragma once
class Enemy
{
public:

	Enemy(const Vector2f& position, int size, float speed);
	~Enemy();

	void Draw() const;

	void Update(float elapsedSec, const Vector2f& nextWaypoint);
	void Move(float elapsedSec);

	float GetDistance();

private:

	Vector2f m_Position;
	Vector2f m_NextPosition;
	int m_Size;
	float m_Speed;
};

