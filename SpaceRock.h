#pragma once
#include "Entity.h"
#include "EnemyList.h"

struct RockFrame
{
	Vector2		pos;
	int			health;
	AABB_Cube	collider;
};

class SpaceRock : public Entity
{
public:
	SpaceRock(aie::Texture* texture, EnemyType ID);
	~SpaceRock();

	//Returns health from the Entity Frame
	float	getHealth()			override;
	//Returns if health is at or below 0. Used in cleaning up dead Entities
	bool	checkHealthIsZero() override;

	//Updates necessary items. Parameters take a float (deltaTime), pointer to a ShipFrame, and a DynamicArray of bullet pointers.
	void	update(float deltaTime, ShipFrame* ship)	override;
	//Draws all necessary elements. Parameters take a pointer to a aie::Renderer2D
	void	draw(aie::Renderer2D* renderer)											override;


private:
	//Never use these
	ShipFrame*				getFrame()			{ return NULL; }

	void createSmallRock();
	void createMediumRock();
	void createLargeRock();

	RockFrame	m_frame;
	float		m_damage;
	float		m_velocity;
};