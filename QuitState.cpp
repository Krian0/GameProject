#include "QuitState.h"

QuitState::QuitState()
{

}


void QuitState::onEnter()
{
	Request quit = { QUIT, QUIT };
	m_requests.push_back(quit);
}

void QuitState::onExit()
{

}

void QuitState::onPushed()
{

}

void QuitState::onPopped()
{

}