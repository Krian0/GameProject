#pragma once
#include "Texture.h"
#include "EnemyList.h"
#include "AABB_Cube.h"
#include "Renderer2D.h"
#include <DynamicArray.h>

struct ShipFrame
{
	AABB_Cube collider;
	Vector2 pos;
	float health;
	bool invulnerable;
	bool setUpInvulnerable;
};

class Entity
{
public:
	Entity() {}
	virtual ~Entity() {}

	//Returns m_alive
	bool			checkAlive();
	//Returns health from the Entity Frame
	virtual float	getHealth() = 0;
	//Returns if health is at or below 0. Used in cleaning up dead Entities
	virtual bool	checkHealthIsZero() = 0;

	//Updates necessary items. Parameters take a float (deltaTime), pointer to a ShipFrame, and a DynamicArray of bullet pointers.
	virtual void update(float deltaTime, ShipFrame* ship) = 0;
	//Draws all necessary elements. Parameters take a pointer to a aie::Renderer2D
	virtual void draw(aie::Renderer2D* renderer) = 0;

	virtual ShipFrame*				getFrame() = 0;
	
protected:
	aie::Texture* m_sprite;

	bool m_alive;

private:
};