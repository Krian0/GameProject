#include "SplashState.h"

#pragma region Constructors & Destructors
SplashState::SplashState()
{
	m_texture = new aie::Texture("./textures/ship.png");
	m_timer = 0;
	m_r = 0;
	m_xPos = 0;
	m_yPos = 0;
}

SplashState::~SplashState()
{
	delete m_texture;
}
#pragma endregion


#pragma region Protected
void SplashState::onUpdate(float deltaTime)
{
	//Spin a ship, Pop state after one second
	m_timer += deltaTime;
	Request pop = { POP };

	m_r += 0.002;
	m_xPos += 0.06;
	m_yPos += 0.03;

	if (m_timer > 1.0f)
		m_requests.push_back(pop);
}

void SplashState::onDraw(aie::Renderer2D* renderer)
{
	renderer->drawSprite(m_texture, m_xPos, m_yPos, 100, 100, m_r, 0);
}


void SplashState::onEnter()
{
	m_currentState = SPLASH;
}

void SplashState::onExit()
{

}

void SplashState::onPushed()
{
	m_requests.clear();
	m_timer = 0;
}

void SplashState::onPopped()
{
	Request menu = {PUSH, MENU};
	m_requests.push_back(menu);
}

States SplashState::get_eState()
{
	return m_currentState;
}
#pragma endregion