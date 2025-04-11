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

	void Buy(Vector2f mousePos);
	//setters

	void SetShooting(Enemy* enemy);
	void SetActive();


	//getters

	Rectf GetRange();

	bool IsActive();
	bool IsShooting();

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

