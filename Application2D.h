#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Audio.h"
//
#include "Matrix2.h"
#include "Matrix3.h"

#include "GameStateManager.h"
#include "SplashState.h"
#include "MenuState.h"
#include "LoadingState.h"
#include "InGameState.h"
#include "PauseState.h"
#include "GameStateHelpers.h"

#include "Factory.h"

#include <DynamicArray.h>
#include <vector>
using std::vector;

class Application2D : public aie::Application 
{
public:

	Application2D();
	virtual ~Application2D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();
	
protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Texture*		m_texture;
	aie::Font*			m_font;
	aie::Audio*			m_audio;

	float	m_cameraX, m_cameraY;
	float	m_timer;
	float	m_deathTimer;
	float	m_delay;
	bool	m_hasRun;
	bool	m_isDead;
	bool	m_unpaused;
	int		m_tick;

	//
	GameStateManager*		m_stateManager;
	Factory*				m_factory;
	States					m_eState;


	Entity*					m_player;
	DynamicArray<Entity*>	m_enemyRocks;

};