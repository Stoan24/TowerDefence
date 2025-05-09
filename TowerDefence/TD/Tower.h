#pragma once
class Bullet;
class Enemy;

class Tower
{
public:
	Tower(Vector2f position);
	~Tower();

	void Draw() const;
	void Update(float elapsedSec);

	//setters

	void SetShooting(Enemy* enemy);

	void RemoveEnemy();

	void ChangeShootState(bool isShooting);

	bool IsFocusEnemyInRange();

	//getters

	Rectf GetRange();

	bool HasEnemy();

private:

	enum class State
	{
		Inactive,
		Shooting
	};

	bool m_IsShooting;

	State m_TowerState;
	Rectf m_Position;
	Rectf m_Range;
	int m_Damage;
	float m_Size;

	//Bullet* m_pBullet;

	float m_ShootTimer;


	Enemy* m_pFocusEnemy;

	float m_BulletTimer;
	bool m_IsBulletVisible;
};

