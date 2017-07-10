#pragma once
#include "GameState.h"
class PauseState : public GameState
{
public:

	PauseState();
	virtual ~PauseState() {}

protected:
	//Updates all necessary elements. Parameters take a float (deltaTime)
	void onUpdate(float deltaTime) override;
	//Draws all necessary elements. Parameters take a pointer to a aie::Renderer2D
	void onDraw(aie::Renderer2D* renderer) override;

	void	onEnter()		override;	//Code for when the state is entered
	void	onExit()		override;	//Code for when the state is exited
	void	onPushed()		override;	//Code for when the state is pushed
	void	onPopped()		override;	//Code for when the state is popped

	//Return current eState
	States	get_eState()	override;
};