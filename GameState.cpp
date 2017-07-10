#include "GameState.h"

#pragma region Public
bool GameState::isActive() const 
{ 
	return m_active; 
}
#pragma endregion


#pragma region Protected
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
#pragma endregion