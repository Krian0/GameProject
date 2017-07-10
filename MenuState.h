#pragma once
#include "AABB_Cube.h"
#include "GameState.h"
#include "Vector2.h"
#include "Audio.h"
#include "Font.h"

class MenuState : public GameState
{
public:

	MenuState();
	virtual ~MenuState();

protected:
	//Updates all necessary elements. Parameters take a float (deltaTime)
	void	onUpdate(float deltaTime) override;
	//Draws all necessary elements. Parameters take a pointer to a aie::Renderer2D
	void	onDraw(aie::Renderer2D* renderer) override;

	void	onEnter()		override;		//Code for when the state is entered
	void	onExit()		override;		//Code for when the state is exited
	void	onPushed()		override;		//Code for when the state is pushed
	void	onPopped()		override {};	//Code for when the state is popped

	//Return current eState
	States	get_eState()	override;

private:
	
	float		    m_bgPos;
	float		    m_bgPos2;
	bool			m_introDone;
	bool			m_playH;
	bool			m_quitH;
	bool			m_sleep;
	Vector2			m_shipPos;
	
	aie::Texture*	m_bg;
	aie::Texture*	m_bg2;
	aie::Texture*	m_ship;
	aie::Font*		m_tFont;
	aie::Font*		m_sFont;
	aie::Font*		m_font;
	aie::Audio*		m_audio;

	AABB_Cube*		m_playBox;
	AABB_Cube*		m_quitBox;

	char*	m_select = "Press enter to select";
	char*	m_title	 = "Space Race";
	char*	m_play	 = "Play";
	char*	m_quit	 = "Quit";
};