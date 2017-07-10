#include "PlayerShip.h"

PlayerShip::PlayerShip(aie::Texture* bulletTexture)
{
	m_sprite	= new aie::Texture("./textures/ship.png");
	m_frame		= new ShipFrame();


	m_velocity		= 6;
	m_timer			= 0;
	m_introDone		= false;
	m_alive			= true;

	m_frame->pos = Vector2(-700, -200);
	m_frame->collider = AABB_Cube(m_frame->pos, Vector2(100, 100));
	m_frame->health = 4;
	m_frame->invulnerable = false;

}

PlayerShip::~PlayerShip()
{
}


float PlayerShip::getHealth()
{
	return m_frame->health;
}

bool PlayerShip::checkHealthIsZero()
{
	return m_frame->health <= 0;
}

void PlayerShip::update(float deltaTime, ShipFrame* ship)
{
	aie::Input* input = aie::Input::getInstance();

	//Sets up timer for invulnerability, later disables if a certain amount of time has passed
	m_timer			+= deltaTime;

	if (m_frame->setUpInvulnerable == true)
		onInvulnerable();


	//Fly ship in from off screen
	if (m_introDone == false)
	{
		if (m_frame->pos.x < 640)
			m_frame->pos.x += 130 * deltaTime;

		if (m_frame->pos.x > 240)
			m_frame->pos.x += 100 * deltaTime;

		if (m_frame->pos.y < 360)
			m_frame->pos.y += 82 * deltaTime;

		if (m_frame->pos.x > 639 && m_frame->pos.y > 359)
			m_introDone = true;

		m_frame->collider.SetMidPos_Direct(m_frame->pos);
	}

	//Handle input and correct collider
	if (m_introDone == true)
	{
		float  Speed = (30 * m_velocity) * deltaTime;

		if (input->isKeyDown(aie::INPUT_KEY_UP) && m_frame->pos.y < 720)
			m_frame->pos.y += Speed;

		if (input->isKeyDown(aie::INPUT_KEY_DOWN) && m_frame->pos.y > 0)
			m_frame->pos.y -= Speed;

		if (input->isKeyDown(aie::INPUT_KEY_LEFT) && m_frame->pos.x > 0)
			m_frame->pos.x -= Speed;

		if (input->isKeyDown(aie::INPUT_KEY_RIGHT) && m_frame->pos.x < 1280)
			m_frame->pos.x += Speed;


		m_frame->collider.SetMidPos_Direct(m_frame->pos);
	}

	if (m_timer > 2)
	{
		m_frame->invulnerable = false;
	}
}

void PlayerShip::draw(aie::Renderer2D * renderer)
{
	renderer->drawSprite(m_sprite, m_frame->pos.x, m_frame->pos.y, 100, 100, 4.71);
}


ShipFrame* PlayerShip::getFrame()
{
	return m_frame;
}

void PlayerShip::onInvulnerable()
{
	m_timer = 0;
	m_frame->setUpInvulnerable = false;
}