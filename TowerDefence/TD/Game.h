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
	explicit Game(const Window& window);
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game(Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update(float elapsedSec) override;
	void Draw() const override;

	// Event handling
	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e) override;
	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e) override;
	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e) override;
	void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e) override;
	void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e) override;

private:

	enum class GameState {
		none,
		start,
		mainloop,
		gameOver
	};

	GameState m_GameState{ GameState::none };


	// FUNCTIONS
	void Initialize();
	void Cleanup();
	void ClearBackground() const;

	void InitGame();

	void InitPath();

	void SetState(GameState state);

	void MakeNewWave();

	//MEMBERS

	Rectf m_Playfield{ 0.f, 0.f, 500.f, GetViewPort().height };

	Rectf m_InfoField{ 500.f, 0.f, 200.f, GetViewPort().height};
	
	Rectf m_FutureField{ 525.f, 25.f, 150.f, 150.f};

	int m_Lives{ 20 };

	Texture* m_LivesText;
	Texture* m_RoundText;
	Texture* m_TowerText;


	bool m_ShowPlacement;

	int m_RoundNr{ 1 };

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

	

	//path
	Path* m_pCurrentPath;
	Path* m_pFuturePath;



	// tower
	std::vector<Tower*> m_pTowers;


	//enemy
	std::vector<Enemy*> m_pEnemies;

	float m_Speed{ 150.f };
};