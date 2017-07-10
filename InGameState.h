#pragma once
#include "GameState.h"
#include "Audio.h"

class InGameState : public GameState
{
public:

	InGameState();
	virtual ~InGameState();

	//Sets m_sleep to bool parameter. Used for Pausing
	void toggleMapPause(bool toggle);

protected:
	//Updates all necessary elements. Parameters take a float (deltaTime)
	void	onUpdate(float deltaTime)			override;
	//Draws all necessary elements. Parameters take a pointer to a aie::Renderer2D
	void	onDraw(aie::Renderer2D* renderer)	override;

	void	onEnter()		override;  //Code for when the state is entered
	void	onExit()		override;  //Code for when the state is exited
	void	onPushed()		override;  //Code for when the state is pushed
	void	onPopped()		override;  //Code for when the state is popped

	//Return current eState
	States	get_eState()	override;

private:

	aie::Texture*	m_map;
	aie::Texture*	m_mapTop;
	aie::Audio*		m_audio;

	float	m_mapPos;
	float	m_mapTopPos;

	float	m_timer;
	bool	m_sleep;
	bool	m_once;
};