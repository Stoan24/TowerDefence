#pragma once
class Bullet;
class Enemy;

class Tower
{
public:
	Tower(Vector2f position);
	~Tower();

	void Draw() const;

	void Buy(Vector2f mousePos);

	Rectf GetRange();

	void SetShooting(Enemy* enemy);
	void SetActive();


	void Update(float elapsedSec);

	bool IsActive();

	bool HasEnemy();

private:

	enum State
	{
		Inactive,
		Active,
		Shooting
	};

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

