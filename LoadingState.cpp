#include "LoadingState.h"

LoadingState::LoadingState()
{
	m_font = new aie::Font("./font/consolas.ttf", 22);
	m_counter = -1;
	m_rounds = 0;
	m_timer = 0;
}

LoadingState::~LoadingState()
{
	delete m_font;
}


void LoadingState::onUpdate(float deltaTime)
{
	//Essentially creates a fake loading screen
	m_timer += deltaTime;

	if (m_timer > 1.0f)
	{
		m_timer = 0;
		m_counter += 1;
	}

	if (m_counter > 3)
	{
		m_counter = 0;
		m_rounds += 1;
	}

	//Pop state after showing text for two rounds
	Request popMe = { POP, LOADING };

	if (m_rounds == 2)
		m_requests.push_back(popMe);
}

void LoadingState::onDraw(aie::Renderer2D* renderer)
{
	renderer->setRenderColour(1, 1, 1, 1);

	if (m_counter == 0)
		renderer->drawText(m_font, m_t1, 640, 360);

	if (m_counter == 1)
		renderer->drawText(m_font, m_t2, 640, 360);

	if (m_counter == 2)
		renderer->drawText(m_font, m_t3, 640, 360);

	if (m_counter == 3)
		renderer->drawText(m_font, m_t4, 640, 360);
}

void LoadingState::onEnter()
{
	m_currentState = LOADING;
}

void LoadingState::onExit()
{
	m_counter = -1;
	m_rounds  = 0;
	m_timer   = 0;
}

void LoadingState::onPopped()
{
	Request play = { PUSH, INGAME };
	m_requests.push_back(play);
}

States LoadingState::get_eState()
{
	return m_currentState;
}