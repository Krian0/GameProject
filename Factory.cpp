#include "Factory.h"


Factory::Factory()
{
	m_bulletTexture		= new aie::Texture("./textures/bullet.png");
	m_smallRockTexture	= new aie::Texture("./textures/rock_small.png");
	m_mediumRockTexture	= new aie::Texture("./textures/rock_medium.png");
	m_largeRockTexture	= new aie::Texture("./textures/rock_large.png");

	m_playerExists = false;
}

Factory::~Factory()
{
	delete m_bulletTexture;
	delete m_smallRockTexture;
	delete m_mediumRockTexture;
	delete m_largeRockTexture;
}

bool Factory::isPlayerAlive(Entity* player)
{
	if (player == nullptr)
		return false;

	return true;
}


Entity* Factory::spawnPlayer()
{
	if (m_playerExists == false)
	{
		return new PlayerShip(m_bulletTexture);
		m_playerExists = true;
	}

	return nullptr;
}

Entity* Factory::spawnEnemy(EnemyType ID)
{
	switch (ID)
	{
	default:
		return nullptr;
		break;

	case SMALL_ROCK:
		return new SpaceRock(m_smallRockTexture, ID);
		break;

	case MEDIUM_ROCK:
		return new SpaceRock(m_mediumRockTexture, ID);
		break;

	case LARGE_ROCK:
		return new SpaceRock(m_largeRockTexture, ID);
		break;
	}
}