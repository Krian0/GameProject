#include "SpaceRock.h"
#include <stdlib.h>
#include <time.h>   

SpaceRock::SpaceRock(aie::Texture* texture, EnemyType ID)
{
	srand(unsigned(time(NULL)));
	int yPos = rand() % 720;
	
	m_alive		= true;
	m_frame.pos = Vector2(1300, yPos);
	m_sprite	= texture;

	if (ID == SMALL_ROCK)
		createSmallRock();

	if (ID == MEDIUM_ROCK)
		createMediumRock();

	if (ID == LARGE_ROCK)
		createLargeRock();
}

SpaceRock::~SpaceRock()
{
}


float SpaceRock::getHealth()
{
	return m_frame.health;
}

bool SpaceRock::checkHealthIsZero()
{
	return m_frame.health <= 0;
}

void SpaceRock::update(float deltaTime, ShipFrame* ship)
{
	//Move and correct frame.collider pos
	m_frame.pos.x -= ((20 * m_velocity) * deltaTime);
	m_frame.collider.SetMidPos_Direct(m_frame.pos);


	//Detect any collision with a PlayerShip, adjust health of both Ship and Rock
	if (m_frame.collider.CheckCubeOverlap(ship->collider) == true && ship->invulnerable == false)
	{
		if (ship->invulnerable == false)
		{
			ship->health -= m_damage;
			ship->invulnerable = true;
			ship->setUpInvulnerable = true;
		}

		m_frame.health--;
	}		

	if (m_frame.pos.x < -100)
		m_alive = false;
}

void SpaceRock::draw(aie::Renderer2D* renderer)
{
	renderer->drawSprite(m_sprite, m_frame.pos.x, m_frame.pos.y);
}

void SpaceRock::createSmallRock()
{
	m_damage = 0.25;
	m_velocity = 5;
	m_frame.health = 1;
	m_frame.collider = AABB_Cube(m_frame.pos, Vector2(11 , 10));
}

void SpaceRock::createMediumRock()
{
	m_damage = 0.5;
	m_velocity = 4;
	m_frame.health = 2;
	m_frame.collider = AABB_Cube(m_frame.pos, Vector2(20, 25));
}

void SpaceRock::createLargeRock()
{
	m_damage = 1;
	m_velocity = 3.5;
	m_frame.health = 3;
	m_frame.collider = AABB_Cube(m_frame.pos, Vector2(34.5, 37.5));
}