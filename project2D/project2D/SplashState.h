#pragma once
#include "GameState.h"
#include "SpriteObject.h"

namespace aie 
{
	class Font;
}

class SplashState : public GameState
{
public:

	SplashState();
	SplashState(aie::Font* font, aie::Texture* spriteTexture, Vector2 spritePos, Vector2 spriteDimensions);
	virtual ~SplashState() {}

protected:

	void onUpdate(float deltaTime)			override;
	void onDraw(aie::Renderer2D* Renderer)	override;

	void onEnter()	override;
	void onExit()	override;
	void onPushed()	override;
	void onPopped()	override;

private:
	
	aie::Font* m_font;
	SpriteObject m_sprite;
};