#include "MenuState.h"
#include "Input.h"

MenuState::MenuState()
{
	m_bgPos		= 1840;
	m_bgPos2	= m_bgPos + 4000;
	m_shipPos	= Vector2(-700, -200); 

	m_bg		= new aie::Texture	("./textures/spaceScroll.png");
	m_bg2		= new aie::Texture	("./textures/spaceScroll.png");
	m_ship		= new aie::Texture	("./textures/ship.png");
	m_tFont		= new aie::Font		("./font/SinRazon.ttf", 68);
	m_sFont		= new aie::Font		("./font/consolas.ttf", 22);
	m_font		= new aie::Font		("./font/SinRazon.ttf", 42);
	m_audio		= new aie::Audio	("./audio/bonusRage.wav");
	
	m_playBox	= new AABB_Cube(Vector2(900, 340), Vector2(100, 50));
	m_quitBox	= new AABB_Cube(Vector2(900, 180), Vector2(100, 50));

	m_introDone = false;
	m_sleep		= false;
}

MenuState::~MenuState()
{
	delete m_bg;
	delete m_bg2;
	delete m_ship;

	delete m_tFont;
	delete m_sFont;
	delete m_font;
	
	delete m_audio;
	
	delete m_playBox;
	delete m_quitBox;

	delete m_select;
	delete m_title;
	delete m_play;
	delete m_quit;
}


void MenuState::onUpdate(float deltaTime)
{
	if (m_sleep != true)
	{
		aie::Input* input = aie::Input::getInstance();

		//Scrolls background map
		m_bgPos		-= 100 * deltaTime;
		m_bgPos2	-= 100 * deltaTime;

		if (m_bgPos2 <= 1840)
		{
			m_bgPos = 1840;
			m_bgPos2 = m_bgPos + 4000;
		}

		//Makes the ship fly onto the screen
		if (m_introDone == false)
		{
			if (m_shipPos.x < 640)
				m_shipPos.x += 130 * deltaTime;

			if (m_shipPos.x > 240)
				m_shipPos.x += 100 * deltaTime;

			if (m_shipPos.y < 360)
				m_shipPos.y += 82 * deltaTime;

			if (m_shipPos.x > 639 && m_shipPos.y > 359)
				m_introDone = true;
		}

		//Allows player to move the ship to highlight and/or select menu items
		if (m_introDone == true)
		{
			float Speed = (90 * 2) * deltaTime;
			if (input->isKeyDown(aie::INPUT_KEY_UP))
				m_shipPos.y += Speed;

			if (input->isKeyDown(aie::INPUT_KEY_DOWN))
				m_shipPos.y -= Speed;

			if (input->isKeyDown(aie::INPUT_KEY_LEFT))
				m_shipPos.x -= Speed;

			if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
				m_shipPos.x += Speed;


			m_playH = m_playBox->CheckCubeOverlap(m_shipPos);
			m_quitH = m_quitBox->CheckCubeOverlap(m_shipPos);


			if (input->isKeyDown(aie::INPUT_KEY_ENTER) && m_playH == true)
			{
				Request load = { PUSH, LOADING };
				m_requests.push_back(load);
			}

			if (input->isKeyDown(aie::INPUT_KEY_ENTER) && m_quitH == true)
			{
				Request quit = { QUIT, MENU };
				m_requests.push_back(quit);
			}
		}
	}
}

void MenuState::onDraw(aie::Renderer2D* renderer)
{
	if (m_sleep != true)
	{
		renderer->drawSprite(m_bg, m_bgPos, 360, 4000, 720, 0, 98);
		renderer->drawSprite(m_bg2, m_bgPos2, 360, 4000, 720, 0, 99);
		renderer->drawSprite(m_ship, m_shipPos.x, m_shipPos.y, 100, 100, 4.71, 10);

		renderer->setRenderColour(1, 1, 1, 1);
		renderer->drawText(m_tFont, m_title, 540, 500);

		//Logic for highlighting the text the player is hovering over
		if (m_introDone == true)
		{
			if (m_playH == true)
			{
				renderer->setRenderColour(1, 1, 0, 1);
				renderer->drawText(m_sFont, m_select, 840, 320);
			}
			else
				renderer->setRenderColour(1, 1, 1, 1);

			renderer->drawText(m_font, m_play, 840, 340);

			if (m_quitH == true)
			{
				renderer->setRenderColour(1, 1, 0, 1);
				renderer->drawText(m_sFont, m_select, 840, 160);
			}
			else
				renderer->setRenderColour(1, 1, 1, 1);

			renderer->drawText(m_font, m_quit, 840, 180);
		}
	}
}


void MenuState::onEnter()
{
	m_sleep = false;

	m_audio->play();
	m_audio->setLooping(true);

	m_requests.clear();

	m_currentState = MENU;
}

void MenuState::onExit()
{
	m_sleep = true;

	m_audio->setLooping(false);
	m_audio->stop();

	m_bgPos		= 1840;
	m_bgPos2	= m_bgPos + 4000;
	m_introDone = false;
	m_playH		= false;
	m_quitH		= false;
	m_shipPos	= Vector2(-700, -200);
}

void MenuState::onPushed()
{
	m_requests.clear();
}

States MenuState::get_eState()
{
	return m_currentState;
}