#pragma once
#include "BaseGame.h"
#include "vector"

class Texture;

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

	void InitWaypoints();

	//MEMBERS

	Texture* m_Map;

	std::vector<Vector2f> m_Waypoints
	{
		Vector2f(GetViewPort().width, GetViewPort().height - 175),
		Vector2f(GetViewPort().width - 150, GetViewPort().height - 175),
		Vector2f(GetViewPort().width - 150, GetViewPort().height - 75),
		Vector2f(GetViewPort().width - 275, GetViewPort().height - 75),
		Vector2f(GetViewPort().width - 275, GetViewPort().height - 175),
		Vector2f(150, GetViewPort().height - 175),
		Vector2f(150, 225),
		Vector2f(400, 225),
		Vector2f(400, 125),
		Vector2f(275, 125),
		Vector2f(275, 0)
	};

	std::vector<Vector2f> m_WaypointsTop;

	Rectf m_TestTower
	{
		275, 170, 40, 40
	};
};