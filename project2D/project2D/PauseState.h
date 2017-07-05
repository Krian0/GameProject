#pragma once
#include "GameState.h"
class PauseState : public GameState
{
public:

	PauseState() {}
	virtual ~PauseState() {}

protected:

	void onUpdate(float deltaTime) override;
	void onDraw(aie::Renderer2D* Renderer) override;

	void onEnter() override;
	void onExit() override;
	void onPushed() override;
	void onPopped() override;
};