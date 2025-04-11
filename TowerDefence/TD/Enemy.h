#pragma once
class Path;


class Enemy
{
public:

	Enemy(const Vector2f& position, int size, float speed, int lifePoints, Path* path);
	~Enemy();

	void Draw() const;

	void Update(float elapsedSec);
	void Move(float elapsedSec);

	float GetDistance();

	bool IsInRange(Rectf towerRange);

	Vector2f GetPosition();

	void IsHit(int damage);

	bool IsDead();

private:

	Vector2f m_Position;
	Vector2f m_NextPosition;

	int m_Size;
	float m_Speed;

	const int m_MaxLifePoints;
	int m_LifePoints;

	Path* m_Path;
	int m_CurrentWaypoint{ 1 };


};

