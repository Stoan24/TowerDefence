#include "pch.h"
#include "Game.h"
#include "Texture.h"
#include "utils.h"
#include "Enemy.h"
#include "Path.h"
#include "Tower.h"
#include "iostream"


Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	InitPath();

	MakeNewWave();

	InitGame();

	m_LivesText = new Texture("Lives: 20", "Minecraft.ttf", 25.f, Color4f(0.f, 0.f, 0.f, 1.f));
	m_RoundText = new Texture("Press \'SPACE\' to start round", "Minecraft.ttf", 12.f, Color4f(0.f, 0.f, 0.f, 1.f));
	m_TowerText = new Texture("Towers: 3", "Minecraft.ttf", 25.f, Color4f(0.f, 0.f, 0.f, 1.f));

}

void Game::Cleanup( )
{

	delete m_pCurrentPath;

	m_pCurrentPath = nullptr;

	for (int i{ 0 }; i < m_pEnemies.size(); i++)
	{
		delete m_pEnemies.at(i);
		m_pEnemies.at(i) = nullptr;
	}

	for (int i{ 0 }; i < m_pTowers.size(); i++)
	{
		delete m_pTowers.at(i);
		m_pTowers.at(i) = nullptr;
	}

	delete m_LivesText;
	m_LivesText = nullptr;

	delete m_TowerText;
	m_TowerText = nullptr;

	delete m_RoundText;
	m_RoundText = nullptr;

	delete m_pFuturePath;

	m_pFuturePath = nullptr;
}

void Game::Update( float elapsedSec )
{

	m_ShowPlacement = false;

	// Check keyboard state
	const Uint8 *pKeyboardStates = SDL_GetKeyboardState( nullptr );

	switch (m_GameState)
	{
	case Game::GameState::none:
		break;
	case Game::GameState::start:

		if (pKeyboardStates[SDL_SCANCODE_SPACE])
		{
			SetState(GameState::mainloop);

			m_RoundText = new Texture("Round: 1", "Minecraft.ttf", 25.f, Color4f(0.f, 0.f, 0.f, 1.f));
		}
		break;
	case Game::GameState::mainloop:

		for (int t{ 0 }; t < m_pTowers.size(); t++)
		{

			for (int e{ 0 }; e < m_pEnemies.size(); e++)
			{

				if (m_pTowers.at(t)->HasEnemy())
				{
					if (!m_pTowers.at(t)->IsFocusEnemyInRange())
					{
						m_pTowers.at(t)->RemoveEnemy();
						m_pTowers.at(t)->ChangeShootState(false);
					}
				}
				else
				{
					if (m_pEnemies.at(e)->IsInRange(m_pTowers.at(t)->GetRange()))
					{
						m_pTowers.at(t)->SetShooting(m_pEnemies.at(e));
					}
				}
			}
			m_pTowers.at(t)->Update(elapsedSec);
		}

		if (m_Lives <= 0)
		{
			SetState(GameState::gameOver); 
			break;
		}

		for (int e{ 0 }; e < m_pEnemies.size(); e++)
		{
			m_pEnemies.at(e)->Update(elapsedSec);
			
			if (m_pEnemies.at(e)->IsDead())
			{
				//remove enemy at that position in the vector
				m_pEnemies.erase(m_pEnemies.begin() + e);
				// remove the enemy from the turret focus
				
				for (int t{ 0 }; t < m_pTowers.size(); t++)
				{
					m_pTowers.at(t)->RemoveEnemy();
				}
			}
			else if (m_pEnemies.at(e)->ReachedEnd())
			{
				m_Lives--;

				delete m_LivesText;
				m_LivesText = nullptr;

				std::string text{ "Lives: " + std::to_string(m_Lives) };

				m_LivesText = new Texture(text, "Minecraft.ttf", 25.f, Color4f(0.f, 0.f, 0.f, 1.f));

				//remove enemy at that position in the vector
				m_pEnemies.erase(m_pEnemies.begin() + e);
				// remove the enemy from the turret focus

				for (int t{ 0 }; t < m_pTowers.size(); t++)
				{
					m_pTowers.at(t)->RemoveEnemy();
				}
			}
		}

		if (m_pEnemies.size() == 0)
		{
			if (pKeyboardStates[SDL_SCANCODE_SPACE])
			{
				m_RoundNr++;

				m_pCurrentPath = m_pFuturePath;

				m_pFuturePath = (new Path(m_Playfield));

				MakeNewWave();

				delete m_RoundText;
				m_RoundText = nullptr;

				std::string text{ "Round: " + std::to_string(m_RoundNr)};
				m_RoundText = new Texture(text, "Minecraft.ttf", 25.f, Color4f(0.f, 0.f, 0.f, 1.f));
			}
		}


		break;
	case Game::GameState::gameOver:

		break;
	default:
		break;
	}

	delete m_TowerText;
	m_TowerText = nullptr;

	std::string text{ "Towers: " + std::to_string((m_RoundNr + 2) - m_pTowers.size()) };
	m_TowerText = new Texture(text, "Minecraft.ttf", 25.f, Color4f(0.f, 0.f, 0.f, 1.f));
}

void Game::Draw( ) const
{
	ClearBackground( );
	
	


	switch (m_GameState)
	{
	case Game::GameState::none:
		break;
	case Game::GameState::start:

		break;
	case Game::GameState::mainloop:
		break;
	case Game::GameState::gameOver:
		break;
	default:
		break;
	}

	//path
	m_pCurrentPath->Draw();

	//enemy
	
	//m_Enemy->Draw();

	for (int i{ 0 }; i < m_pEnemies.size(); i++)
	{
		m_pEnemies.at(i)->Draw();
	}

	//tower

	int mouseX{}, mouseY{};
	Uint32 pressed = SDL_GetMouseState(&mouseX, &mouseY);

	mouseY = GetViewPort().height - mouseY;

	if (pressed && SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		utils::SetColor(Color4f(0.f, 1.f, 0.f, 0.5f));
		utils::FillRect(mouseX - 10.f, mouseY - 10.f, 20.f, 20.f);

		utils::SetColor(Color4f(1.f, 1.f, 0.f, 0.5f));
		utils::DrawRect(mouseX - 60.f, mouseY - 60.f, 120.f, 120.f);
	}

	for (int i{ 0 }; i < m_pTowers.size(); i++)
	{
		m_pTowers.at(i)->Draw();
	}


	//infofield
	utils::SetColor(Color4f(0.f, 1.f, 1.f, 1.f));
	utils::FillRect(m_InfoField);

	utils::SetColor(Color4f(0.f, 0.f, 0.f, 1.f));
	utils::FillRect(m_FutureField);

	

	//text
	m_LivesText->Draw(Vector2f(520.f, 350.f));
	m_RoundText->Draw(Vector2f(520.f, 450.f));
	m_TowerText->Draw(Vector2f(520.f, 300.f));


	Rectf m_FutureField{ 525.f, 25.f, 150.f, 150.f };


	glPushMatrix();

	glTranslatef(525.f, 25.f, 0.f);

	glScalef(0.3f, 0.3f, 1.f);

	m_pFuturePath->Draw();
	glPopMatrix();

}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:

		m_ShowPlacement = true;

		break;
	case SDL_BUTTON_RIGHT:
		std::cout << " right button " << std::endl;
		break;
	case SDL_BUTTON_MIDDLE:
		std::cout << " middle button " << std::endl;
		break;
	}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:

		if (m_GameState != GameState::gameOver)
		{
			if (m_pTowers.size() < m_RoundNr + 2)
			{
				m_pTowers.push_back(new Tower(Vector2f(e.x, e.y)));
			}

		}

		break;
	case SDL_BUTTON_RIGHT:
		std::cout << " right button " << std::endl;
		break;
	case SDL_BUTTON_MIDDLE:
		std::cout << " middle button " << std::endl;
		break;
	}


}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::InitGame()
{
	SetState(GameState::start);
}

void Game::InitPath()
{
	m_pCurrentPath = new Path(m_Playfield);

	m_pFuturePath = new Path(m_Playfield);
}

void Game::SetState(GameState state)
{
	m_GameState = state;
}

void Game::MakeNewWave()
{
	Vector2f positioner{ 1, 1 };
	bool isHorizontal{ false };

	int enemyAmount{ 4 * m_RoundNr };


	switch (m_pCurrentPath->GetEdge())
	{
	case Path::Edge::Top:
		positioner.y = 1;
		break;

	case Path::Edge::Bottom:
		positioner.y = -1;
		break;

	case Path::Edge::Left:
		positioner.x = -1;
		isHorizontal = true;
		break;

	case Path::Edge::Right:
		positioner.x = 1;
		isHorizontal = true;
		break;
	default:
		break;
	}

	Vector2f startPos{ m_pCurrentPath->GetFirstPosition() };
	std::vector<Vector2f> m_FirstWave{};
	
	if (isHorizontal)
	{
		for (int i{ 1 }; i <= enemyAmount; i++)
		{
			//													position									path		type
			m_pEnemies.push_back( new Enemy(Vector2f( startPos.x + ((50.f*i) * positioner.x), startPos.y), m_pCurrentPath, 1));
		}
	}
	else
	{
		for (int i{ 1 }; i < enemyAmount; i++)
		{
			//													position									path		type
			m_pEnemies.push_back(new Enemy(Vector2f( startPos.x, startPos.y + ((50.f * i) * positioner.y)), m_pCurrentPath, 1));
		}
	}
}