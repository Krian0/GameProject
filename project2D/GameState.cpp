#include "GameState.h"

void GameState::enter()
{
	m_active = true;
	onEnter();
}

void GameState::exit()
{
	m_active = false;
	onExit();
}

bool GameState::isActive() const 
{ 
	return m_active; 
}