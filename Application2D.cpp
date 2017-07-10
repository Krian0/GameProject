#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <time.h>

//--------------------------------------------------------------------------------------------------------
//										Game Project: SPACE RACE										//
//																										//
//																										//
//																										//
//											INSTRUCTIONS:												//
//																										//
//		Splash Screen:			Wait a few seconds.														//
//																										//
//		  Menu Screen:			Wait for Ship and Play/Quit options to appear, then use the				//										
//					|			UP/DOWN/LEFT/RIGHT Arrow keys to move ship to an option.				//												
//					|			Press ENTER to select.													//			
//																										//
//	   Loading Screen:			This loading screen is set to wait for a few seconds. It's fake.		//																
//																										//
//		InGame Screen:			Wait for ship to appear on screen. Dodge rocks.			 				//														
//					|			Make it to the end of the level without dying!							//													
//					|																					//
//					|																					//
//					|									DAMAGE VALUES		HEALTH						//
//					|																					//
//					|		Small				Rocks			0.25			1						//							
//					|		Medium				Rocks			0.50			2						//		
//					|		Large				Rocks			1.00			3						//		
//					|																					//
//					|		Player				Bullets			1.00			NA						//
//					|							Player			NA				4.00					//
//					|																					//
//					|		 MOVE:				UP/DOWN/LEFT/RIGHT (Arrow keys)							//
//					|		SHOOT:				E														//
//					|		PAUSE:				SPACE													//
//					|		 MENU:				ESC														//
//					|																					//
//																										//
//																										//
//		 CONTENTS:																						//
//																										//
//		 STARTUP	(GP_ST)																				//
//		 |																								//
//																										//
//		 SHUTDOWN	(GP_SH)																				//
//		 |																								//
//																										//
//		 UPDATE		(GP_U)																				//
//		 |																								//
//																										//
//		 DRAW		(GP_D)																				//
//		 |																								//
//																										//
//--------------------------------------------------------------------------------------------------------


Application2D::Application2D() 
{
}

Application2D::~Application2D() 
{
}

bool Application2D::startup() //(GP_ST)
{

	m_2dRenderer	=	new aie::Renderer2D();
	m_texture		=	new aie::Texture("./textures/bullet.tga");
	m_font			=	new aie::Font("./font/consolas.ttf", 32);
	m_audio			=	new aie::Audio("./audio/powerup.wav");
	m_player		=	nullptr;

	m_cameraX		= 0;
	m_cameraY		= 0;
	m_timer			= 0;
	m_deathTimer	= 0;
	m_delay			= 0;
	m_tick			= 2;
	
	m_stateManager = new GameStateManager((int)States::STATE_COUNT);

	m_stateManager->manageState(REGISTER, new SplashState,	SPLASH);
	m_stateManager->manageState(REGISTER, new MenuState,	MENU);
	m_stateManager->manageState(REGISTER, new LoadingState,	LOADING);
	m_stateManager->manageState(REGISTER, new InGameState,	INGAME);
	m_stateManager->manageState(REGISTER, new PauseState,	PAUSE);
	
	m_stateManager->manageState(PUSH, SPLASH);

	m_hasRun	= false;
	m_unpaused	= false;

	return true;
}

void Application2D::shutdown() //(GP_SH)
{
	delete m_audio;
	delete m_font;
	delete m_texture;
	delete m_2dRenderer;

	delete m_stateManager;
	delete m_factory;
	delete m_player;

	m_enemyRocks.~DynamicArray();
}

void Application2D::update(float deltaTime) //(GP_U)
{
   	aie::Input* input = aie::Input::getInstance();
	m_delay += deltaTime;

	//Run InGame loop while not paused
	if (m_eState == INGAME)
	{
		m_timer += deltaTime;

		if (m_hasRun == false)
		{
			m_factory = new Factory();
			m_hasRun = true;

			m_player = m_factory->spawnPlayer();
		}

		//Press SPACE while INGAME to PAUSE
		if (input->wasKeyPressed(aie::INPUT_KEY_SPACE) && m_delay > 1)
		{
			m_stateManager->manageState(PUSH, PAUSE);
			m_delay = 0;
		}

		//Press ESCAPE while INGAME to QUIT TO MENU
		if (input->wasKeyPressed(aie::INPUT_KEY_ESCAPE))
			m_stateManager->manageState(POP, INGAME);


		//Set random ID and amount of enemies
		if (m_timer > 1)
		{
			srand(unsigned(time(NULL)));
			int		Int_ID = rand() % 2;
			EnemyType	ID;

			if (Int_ID == 0) ID = SMALL_ROCK;
			if (Int_ID == 1) ID = MEDIUM_ROCK;
			if (Int_ID == 2) ID = LARGE_ROCK;

			//Spawn enemies
			m_enemyRocks.push_back(m_factory->spawnEnemy(ID));

			m_timer = 0;
		}


		//Update m_player, then m_enemyRocks
		m_player->update(deltaTime, m_player->getFrame());

		for (auto SpaceRock : m_enemyRocks)
			SpaceRock->update(deltaTime, m_player->getFrame());
	}

	//if (m_unpaused == true)
	//{
	//	m_tick--;

	//	if (m_tick == 0)
	//	{
	//		m_stateManager->switchUnpause(m_unpaused);
	//		m_unpaused = false;
	//	}
	//}


	//Update the GSM and get the current (as of update) eState
	m_stateManager->update(deltaTime);
	m_eState = m_stateManager->get_eState();


	//Run Pause loop
	if (m_eState == PAUSE)
	{
		//Press SPACE while PAUSED to UNPAUSE
		if (input->wasKeyPressed(aie::INPUT_KEY_SPACE) && m_delay > 1)
		{
			m_stateManager->manageState(POP, PAUSE);
			m_unpaused = true;
			m_tick	= 2;
			m_delay = 0;
		}

		//Press ESCAPE while PAUSED to QUIT TO MENU
		if (input->wasKeyPressed(aie::INPUT_KEY_ESCAPE) && m_delay > 1)
		{
			m_stateManager->manageState(QUIT, PAUSE);
			m_delay = 0;
		}
	}


	//Quit if the Quit option was selected from the MENU
	if (m_stateManager->checkStateCount() == 0 && m_stateManager->checkQuitStatus() == true)
	{
		quit();
	}

	if (m_eState != PAUSE && m_eState == INGAME)
	{

		int r = m_enemyRocks.size();

		//Sorts out dead Entities
		if (r > 0)
		{
			int RN = 0;
			for (auto rock : m_enemyRocks)
			{
				bool a = rock->checkAlive();

				if (a == false)
				{
					rock->~Entity();
					m_enemyRocks.erase_at(RN);
				}

				if (a == true)
				{
					if (rock->checkHealthIsZero() == true)
					{
						rock->~Entity();
						m_enemyRocks.erase_at(RN);
					}
				}
				RN++;
			}
		}

		//Cleans PlayerShip
		if (m_player != nullptr)
		{
			bool a = m_player->checkAlive();

			if (a == false)
				m_player->~Entity();

			if (a == true)
				if (m_player->checkHealthIsZero() == true)
					m_player->~Entity();
		}

		//Checks if m_player is nullptr, prepares to return to menu, returns to menu after 3 seconds
		if (m_player == nullptr && m_hasRun == true)
		{
			m_deathTimer += deltaTime;

			if (m_isDead == false)
			{
				m_audio->play();
				m_isDead = true;
			}

			if (m_deathTimer > 3)
				m_stateManager->manageState(POP, INGAME);
		}
	}
}


void Application2D::draw() //(GP_D)
{
	clearScreen();
	m_2dRenderer->setCameraPos(m_cameraX, m_cameraY);
	m_2dRenderer->begin();

	//Draw states
	m_stateManager->draw(m_2dRenderer);

	//Draw m_enemyRocks, then m_enemyShips, then m_player
	if (m_eState == INGAME)
	{
		if (m_enemyRocks.size() > 0)
			for (auto rock : m_enemyRocks)
				rock->draw(m_2dRenderer);

		if (m_player != nullptr)
			m_player->draw(m_2dRenderer);
	}


	m_2dRenderer->end();
}