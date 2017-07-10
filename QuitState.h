#pragma once
#include "GameState.h"
class QuitState : public GameState
{
public:

	QuitState();
	virtual ~QuitState() {}

protected:

	void onUpdate(float deltaTime) override {};
	void onDraw(aie::Renderer2D* renderer) override {};

	void onEnter() override;
	void onExit() override;
	void onPushed() override;
	void onPopped() override;
};