#pragma once
#include "SpaceRock.h"
#include "PlayerShip.h"

class Factory
{
public:
	Factory();
	~Factory();

	//Returns false if Entity* player parameter is a nullptr
	bool isPlayerAlive(Entity* player);

	//Spawns Player, ensures only one can be spawned
	Entity* spawnPlayer();
	//Spawns enemy based on EnemyType (enum) ID parameter
	Entity* spawnEnemy(EnemyType ID);

private:
	aie::Texture* m_bulletTexture;
	aie::Texture* m_smallRockTexture;
	aie::Texture* m_mediumRockTexture;
	aie::Texture* m_largeRockTexture;

	bool m_playerExists;
};