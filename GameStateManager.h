#pragma once
#include <map>
#include <assert.h>
#include "GameState.h"

class GameStateManager
{ 
public: 
	
	GameStateManager(unsigned int stateCount);
	~GameStateManager();

	//Manages States based on input. Parameters take a Prompt, GameState* and eState.
	void manageState(Prompt Command, GameState* State, States eState);
	//Manages States based on input. Parameters take a Prompt and eState.
	void manageState(Prompt Command, States eState);

	//Updates all necessary elements. Parameters take a float (deltaTime)
	void update(float deltaTime);
	//Draws all necessary elements. Parameters take a pointer to a aie::Renderer2D
	void draw(aie::Renderer2D* renderer);

	//Returns m_stateStack.Size()
	int	 checkStateCount() const;
	//Returns m_quit. Used when exiting to Menu
	bool checkQuitStatus();
	//Sets m_unpause to bool parameter. Used in Pausing
	void switchUnpause(bool value);
	
	//Return current eState
	States get_eState();

protected: 

	//Adds a GameState* to the m_registeredStates array. Parameters take an int ID (index position) and a pointer to a GameState
	void registerState(int id, GameState* state);
	//Pushes back a state from m_registeredStates to m_pushedStates through an int ID (index position) in the parameters
	void pushState(int id);
	//Sets m_popState to true. Used in Popping back states in update
	void popState();
	
	//Returns m_requestQueue.size(). Using in managing states and handling requests
	int			queueSize()			const;
	//Returns a pointer to the top state in m_stateStack
	GameState*	getTopState()		const;
	//Returns a pointer to a state in m_registeredStates based on an int ID (index position) parameter
	GameState*	getState(int id)	const;


	vector<GameState*>	m_stateStack;
	vector<GameState*>	m_registeredStates; 
	vector<GameState*>	m_pushedStates;
	vector<Request>		m_requestQueue;

	States	m_currentState;

	bool	m_popState;
	bool	m_quitFromPause;
	bool	m_quit;
	bool	m_unpause;
};