#pragma once
#include "GameStateHelpers.h"
#include "Renderer2D.h"
#include "Texture.h"
#include <assert.h>
#include <vector>
using std::vector;

class GameState 
{
	friend class GameStateManager;
public: 
	
	GameState() {} 
	virtual ~GameState() {} 


	bool isActive() const; //Returns the bool of m_active

protected: 

	void enter(); //Sets m_active to true, then calls onEnter()
	void exit();  //Sets m_active to false, then calls onExit()
	
	//Updates all necessary elements. Parameters take a float (deltaTime)
	virtual void	onUpdate(float deltaTime) = 0;
	//Draws all necessary elements. Parameters take a pointer to a aie::Renderer2D
	virtual void	onDraw(aie::Renderer2D* renderer) = 0;

	virtual void	onEnter() {} 
	virtual void	onExit() {} 
	virtual void	onPushed() {}
	virtual void	onPopped() {}

	//Return current eState
	virtual States	get_eState() = 0;

	vector<Request> m_requests;
	States			m_currentState;

private: 
	bool	m_active	= false;
};