#pragma once
#include "GameState.h"
class SplashState : public GameState
{
public:

	SplashState();
	virtual ~SplashState();

protected:
	//Updates all necessary elements. Parameters take a float (deltaTime)
	void	onUpdate(float deltaTime)			override;
	//Draws all necessary elements. Parameters take a pointer to a aie::Renderer2D
	void	onDraw(aie::Renderer2D* renderer)	override;

	void	onEnter()		override;	//Code for when the state is entered
	void	onExit()		override;	//Code for when the state is exited
	void	onPushed()		override;	//Code for when the state is pushed
	void	onPopped()		override;	//Code for when the state is popped

	//Return current eState
	States	get_eState()	override;

private:

	aie::Texture*	m_texture;
	float			m_timer;
	float			m_r;
	float			m_xPos;
	float			m_yPos;
};