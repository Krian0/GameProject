#pragma once
#include "GameState.h"
class State : public GameState
{
public:

	State() {}
	virtual ~State() {}

protected:

	void onUpdate(float deltaTime) override;
	void onDraw() override;

	void onEnter() override;
	void onExit() override;
	void onPushed() override;
	void onPopped() override;
};