#include "InGameState.h"

InGameState::InGameState()
{
	m_mapPos	= 7000;
	m_mapTopPos	= 7880;

	m_timer		= 0;
	m_sleep		= false;
	m_once		= false;

	m_map		= new aie::Texture	("./textures/spaceMap2.png");
	m_mapTop	= new aie::Texture	("./textures/starfieldMap.png");
	m_audio		= new aie::Audio	("./audio/shellShockShake.wav");

	assert(m_map	!= nullptr);
	assert(m_mapTop != nullptr);
	assert(m_audio	!= nullptr);
}

InGameState::~InGameState()
{
	delete m_map;
	delete m_mapTop;
	delete m_audio;
}


void InGameState::toggleMapPause(bool toggle)
{
	m_sleep = toggle;
}

void InGameState::onUpdate(float deltaTime)
{
	m_timer += deltaTime;

	if (m_sleep == false && m_mapPos > -5700 && m_timer > 2)
	{
		if (m_once == false) 
		{
			m_audio->play();
			m_once == true;
		}

		if (m_timer > 6)
		{
			m_mapPos -= 110 * deltaTime;
			m_mapTopPos -= 114 * deltaTime;
		}
	}

	if (m_sleep == true)
		m_audio->pause();
}

void InGameState::onDraw(aie::Renderer2D* renderer)
{
	assert(renderer != nullptr);

	renderer->drawSprite(m_map,		m_mapPos,		360, 0, 720, 0, 98);
	renderer->drawSprite(m_mapTop,	m_mapTopPos,	360, 0, 720, 0, 90);
}


void InGameState::onEnter()
{
	m_sleep = false;
	m_currentState = INGAME;
}

void InGameState::onExit()
{
	m_sleep = true;
	m_audio->stop();
	m_requests.clear();
}

void InGameState::onPushed()
{

}

void InGameState::onPopped()
{
	m_requests.clear();
}

States InGameState::get_eState()
{
	return m_currentState;
}