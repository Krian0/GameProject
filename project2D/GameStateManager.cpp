#include "GameStateManager.h"

GameStateManager::GameStateManager(unsigned int stateCount)
{
	m_registeredStates.resize(stateCount);
}

GameStateManager::~GameStateManager() 
{
	for (auto state : m_registeredStates)
		delete state;
}

void GameStateManager::registerState(int id, GameState* state)
{
	m_registeredStates.at(id) = state;
}

void GameStateManager::pushState(int id)
{
	m_pushedStates.push_back(m_registeredStates.at(id));
}

void GameStateManager::popState()
{
	m_popState = true;
}

void GameStateManager::update(float deltaTime)
{
	while (m_popState == true)
	{
		m_popState = false;

		m_stateStack.back()->exit();
		auto temp = m_stateStack.back();
		m_stateStack.pop_back();
		temp->onPopped();

		if (m_stateStack.empty() == false)
			m_stateStack.back()->enter();
	}

	for (auto pushedState : m_pushedStates)
	{
		if (m_stateStack.empty() == false)
			m_stateStack.back()->exit();

		pushedState->onPushed();
		m_stateStack.push_back(pushedState);
		m_stateStack.back()->enter();
	}

	m_pushedStates.clear();

	for (auto state : m_stateStack)
		state->onUpdate(deltaTime);
}

void GameStateManager::draw()
{
	for (auto state : m_stateStack)
		state->onDraw();
}

int GameStateManager::activeStateCount() const 
{ 
	return m_stateStack.size();
}
GameState* GameStateManager::getTopState() const 
{ 
	return m_stateStack.back();
}
GameState* GameStateManager::getState(int id) const 
{ 
	return m_registeredStates.at(id); 
}