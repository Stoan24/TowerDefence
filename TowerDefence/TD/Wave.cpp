#include "pch.h"
#include "Wave.h"
#include "Enemy.h"
#include "Path.h"

Wave::Wave(std::vector<Vector2f> wavePositions, Path* path, int waveNr)
	:m_WaveNr{ waveNr }
{
	for (int i{ 0 }; i < wavePositions.size(); i++)
	{
		m_Enemies.push_back(new Enemy(wavePositions.at(i), path, 1));
	}
}

Wave::~Wave()
{

}

void Wave::Draw() const
{
	for (int i{ 0 }; i < m_Enemies.size(); i++)
	{
		m_Enemies.at(i)->Draw();
	}
}

void Wave::Update(float elapsedSec)
{

}
