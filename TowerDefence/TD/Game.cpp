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

	InitEnemies();

	InitTower();
}

void Game::Cleanup( )
{

}

void Game::Update( float elapsedSec )
{
	// Check keyboard state
	//const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	//if ( pStates[SDL_SCANCODE_RIGHT] )
	//{
	//	std::cout << "Right arrow key is down\n";
	//}
	//if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	//{
	//	std::cout << "Left and up arrow keys are down\n";
	//}
	for (int i{ 0 }; i < m_Enemies.size(); i++)
	{
		m_Enemies.at(i)->Update(elapsedSec);
	}


	for (int tower{ 0 }; tower < m_Towers.size(); tower++)
	{
		//loop towers
		if (m_Towers.at(tower)->IsActive() || m_Towers.at(tower)->IsShooting())
		{
			//loop enemies
			for (int enemy{ 0 }; enemy < m_Enemies.size(); enemy++)
			{
				//check if enemies are in range of the tower
				if (m_Enemies.at(enemy)->IsInRange(m_Towers.at(tower)->GetRange()))
				{
					if (!m_Towers.at(tower)->HasEnemy())
					{
						m_Towers.at(tower)->SetShooting(m_Enemies.at(enemy));
					}
				}
				else
				{
					m_Towers.at(tower)->SetActive();
				}
			}
		}
		m_Towers.at(tower)->Update(elapsedSec);
	}
}

void Game::Draw( ) const
{
	ClearBackground( );

	//path
	m_Path->Draw();

	//enemy
	
	//m_Enemy->Draw();

	for (int i{ 0 }; i < m_Enemies.size(); i++)
	{
		m_Enemies.at(i)->Draw();
	}

	//tower
	for (int i{ 0 }; i < m_Towers.size(); i++)
	{
		m_Towers.at(i)->Draw();
	}
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
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}

	for (int i{ 0 }; i < m_Towers.size(); i++)
	{
		m_Towers.at(i)->Buy(Vector2f(e.x, e.y));
	}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::InitPath()
{
	m_Path = new Path(m_Waypoints);
}

void Game::InitEnemies()
{
	for (int i{ 0 }; i < m_FirstWave.size(); i++)
	{
		m_Enemies.push_back( new Enemy(m_FirstWave.at(i), 10, m_Speed, 20, m_Path));
	}
	//m_Enemy = new Enemy(m_FirstStartPos, 10, m_Speed, 20);
}

void Game::InitTower()
{
	for (int i{ 0 }; i < m_TowerLocations.size(); i++)
	{
		m_Towers.push_back(new Tower(m_TowerLocations.at(i)));
	}
}
