#include "PauseState.h"

PauseState::PauseState()
{

}


void PauseState::onUpdate(float deltaTime)
{

}

void PauseState::onDraw(aie::Renderer2D* renderer)
{

}


void PauseState::onEnter()
{
	m_currentState = PAUSE;
}

void PauseState::onExit()
{
	m_currentState = INGAME;
	m_requests.clear();
}

void PauseState::onPushed()
{

}

void PauseState::onPopped()
{
	m_requests.clear();
}

States PauseState::get_eState()
{
	return m_currentState;
}