#pragma once
#include "Entity.h"
#include "Input.h"

class PlayerShip : public Entity
{
public:
	PlayerShip(aie::Texture* bulletTexture);
	~PlayerShip();

	//Returns health from the Entity Frame
	float	getHealth()			override;
	//Returns if health is at or below 0. Used in cleaning up dead Entities
	bool	checkHealthIsZero() override;

	//Updates necessary items. Parameters take a float (deltaTime), pointer to a ShipFrame, and a DynamicArray of bullet pointers.
	void	update(float deltaTime, ShipFrame* ship)	override;
	//Draws all necessary elements. Parameters take a pointer to a aie::Renderer2D
	void	draw(aie::Renderer2D* renderer)											override;

	//Returns the ShipFrame of the Player
	ShipFrame*				getFrame()			override;


private:
	//Sets up variables intended to make the player invulnerable for a short while after being damaged
	void onInvulnerable();

	ShipFrame*	m_frame;
	float		m_velocity;
	float		m_timer;
	bool		m_introDone;
};
