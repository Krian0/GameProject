#include "GameStateManager.h"

#pragma region Constructors & Destructors
GameStateManager::GameStateManager(unsigned int stateCount)
{
	m_registeredStates.resize(stateCount);
	m_popState		= false;
	m_quitFromPause = false;
	m_quit			= false;
}

GameStateManager::~GameStateManager() 
{
	for (auto state : m_registeredStates)
		delete state;
}
#pragma endregion


#pragma region Public
void GameStateManager::manageState(Prompt command, GameState* state, States eState)
{
	if (command == REGISTER)
		registerState((int)eState, state);
}

void GameStateManager::manageState(Prompt command, States eState)
{
	if (command == PUSH)
		pushState((int)eState);
	
	if (command == POP)
		popState();

	if (command == QUIT)
	{
		if (eState == PAUSE)
			m_quitFromPause = true;

		if (eState == MENU)
			m_quit = true;

		popState();
	}
}


void GameStateManager::update(float deltaTime)
{
	//Check for and execute any Register/Push/Pop Requests from GameStates, then clear both GSM & TopState queue
	if (checkStateCount() > 0)
	{
		if (m_unpause == true)
			getTopState()->m_requests.clear();


		if (m_unpause == false)
		{
			unsigned int Size = getTopState()->m_requests.size();

			if (Size > 0)
			{
				vector<Request> temp = getTopState()->m_requests;

				for (unsigned int i = 0; i < Size - 1; i++)
					m_requestQueue.push_back(temp[i]);
			}
		}

		m_unpause = false;
	}

	if (queueSize() > 0)
	{
		for (auto requests : m_requestQueue)
			manageState(requests.pr, requests.st);

		m_requestQueue.clear();
		
		if (checkStateCount() > 0)
			getTopState()->m_requests.clear();
	}

	//Pop top state if m_popState is true
	while (m_popState == true)
	{
		if (m_quitFromPause == false)
			m_popState = false;

		m_quitFromPause = false;

		m_stateStack.back()->exit();
		auto temp = m_stateStack.back();
		m_stateStack.pop_back();
		temp->onPopped();

		//Check for any final Requests
		for (auto requests : temp->m_requests)
			m_requestQueue.push_back(requests);

		if (m_stateStack.empty() == false)
			m_stateStack.back()->enter();
	}
	
	//Push (then clear) any states queued in m_pushedStates
	for (GameState* pushedState : m_pushedStates)
	{
		if (m_stateStack.empty() == false)
			m_stateStack.back()->exit();

		pushedState->onPushed();
		m_stateStack.push_back(pushedState);
		m_stateStack.back()->enter();
	}

	m_pushedStates.clear();

	//Update all states in m_stateStack and set m_currentState to the current state
	for (auto state : m_stateStack)
	{
		state->onUpdate(deltaTime);
		m_currentState = state->get_eState();
	}
}

void GameStateManager::draw(aie::Renderer2D* renderer)
{
	for (auto state : m_stateStack)
		state->onDraw(renderer);
}


int GameStateManager::checkStateCount() const
{
	return m_stateStack.size();
}

bool GameStateManager::checkQuitStatus()
{
	return m_quit;
}

void GameStateManager::switchUnpause(bool value)
{
	m_unpause = value;
}

States GameStateManager::get_eState()
{
	return m_currentState;
}
#pragma endregion


#pragma region Protected
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

int GameStateManager::queueSize() const
{
	return m_requestQueue.size();
}

GameState* GameStateManager::getTopState() const 
{ 
	return m_stateStack.back();
}

GameState* GameStateManager::getState(int id) const 
{ 
	return m_registeredStates.at(id); 
}
#pragma endregion