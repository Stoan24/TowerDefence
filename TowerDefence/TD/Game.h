#pragma once
#include "BaseGame.h"
#include "vector"

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

	Vector2f m_StartPos{ GetViewPort().width + 20, 325 };

	std::vector<Vector2f> m_Waypoints
	{
		Vector2f(m_StartPos),
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

	std::vector<Tower*> m_Towers;

	int m_CurrentWaypoint{ 1 };
	float m_Speed{ 150.f };

	Enemy* m_Enemy;
	Path* m_Path;
};