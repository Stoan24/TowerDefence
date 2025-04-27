#pragma once
#include "BaseGame.h"
#include "vector"
#include "list"

class Texture;
class Path;
class Enemy;
class Tower;

class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

private:

	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;

	void InitPath();
	void InitEnemies();
	void InitTower();

	//MEMBERS

	// ------level 1 positions------

	Vector2f m_FirstStartPos{ GetViewPort().width + 50, 325 };

	std::vector<Vector2f> m_Waypoints
	{
		Vector2f(m_FirstStartPos),
		Vector2f(450, 325),
		Vector2f(450, 425),
		Vector2f(350, 425),
		Vector2f(350, 325),
		Vector2f(150, 325),
		Vector2f(150, 225),
		Vector2f(400, 225),
		Vector2f(400, 125),
		Vector2f(300, 125),
		Vector2f(300, -20)
	};

	std::vector<Vector2f> m_TowerLocations
	{
		Vector2f(400, 375),
		Vector2f(200, 275),
		Vector2f(350, 175)

	};

	std::vector<Vector2f> m_FirstWave
	{
		Vector2f(m_FirstStartPos),
		Vector2f(m_FirstStartPos.x + 50, m_FirstStartPos.y),
		Vector2f(m_FirstStartPos.x + 100, m_FirstStartPos.y),
		Vector2f(m_FirstStartPos.x + 200, m_FirstStartPos.y),
		Vector2f(m_FirstStartPos.x + 250, m_FirstStartPos.y),
		Vector2f(m_FirstStartPos.x + 300, m_FirstStartPos.y),
		Vector2f(m_FirstStartPos.x + 350, m_FirstStartPos.y)
	};

	//path
	Path* m_Path;



	// tower
	std::vector<Tower*> m_Towers;

	float m_ShootTimer{ 0 };


	//enemy
	std::vector<Enemy*> m_Enemies;

	float m_Speed{ 150.f };


	//test
};