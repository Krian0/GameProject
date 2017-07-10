#pragma once
#include "GameState.h"
#include "Font.h"
#include <string.h>
using std::string;

class LoadingState : public GameState
{
public:

	LoadingState();
	virtual ~LoadingState();

protected:
	//Updates all necessary elements. Parameters take a float (deltaTime)
	void	onUpdate(float deltaTime) override;
	//Draws all necessary elements. Parameters take a pointer to a aie::Renderer2D
	void	onDraw(aie::Renderer2D* renderer) override;

	void	onEnter()		override;		//Code for when the state is entered
	void	onExit()		override;		//Code for when the state is exited
	void	onPushed()		override {}		//Code for when the state is pushed
	void	onPopped()		override;		//Code for when the state is popped

	//Return current eState
	States	get_eState()	override;

private:

	aie::Font*	m_font;

	char* m_t1 = "Loading";
	char* m_t2 = "Loading .";
	char* m_t3 = "Loading . .";
	char* m_t4 = "Loading . . .";

	int	  m_counter;
	int	  m_rounds;
	float m_timer;
};