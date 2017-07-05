#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Audio.h"
//
#include "GameStateManager.h"
#include "Vector2.h"

class Application2D : public aie::Application {
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
	aie::Texture*		m_shipTexture;
	aie::Font*			m_font;
	aie::Audio*			m_audio;
	
	enum class eGameState
	{
		SPLASH = 0,
		MENU,
		OPTIONS,
		LOADING,
		INGAME,
		PAUSE,
		STATE_COUNT
	};

	GameStateManager* m_gameStateManager;

	float m_cameraX, m_cameraY;
	float m_timer;

	//
	Vector2 m_windowSize;
};