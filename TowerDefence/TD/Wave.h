#pragma once
#include <vector>


class Enemy;
class Path;

class Wave
{

public:

	Wave(std::vector<Vector2f> wavePositions, Path* path, int waveNr);
	~Wave();

	void Draw() const;

	void Update(float elapsedSec);


private:

	int m_WaveNr;

	std::vector<Enemy*> m_Enemies;
};

