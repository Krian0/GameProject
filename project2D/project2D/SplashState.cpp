#include "SplashState.h"
#include "Renderer2D.h"

SplashState::SplashState() {}

SplashState::SplashState(aie::Font* font, aie::Texture* spriteTexture, Vector2 spritePos, Vector2 spriteDimensions) : m_font(font)
{
	m_sprite.texture = spriteTexture;
	m_sprite.position = spritePos;
	m_sprite.dimensions = spriteDimensions;
}


void SplashState::onUpdate(float deltaTime)
{

}

void SplashState::onDraw(aie::Renderer2D* Renderer)
{
	Renderer->drawSprite(m_sprite.texture, m_sprite.position.x, m_sprite.position.y, m_sprite.dimensions.x, m_sprite.dimensions.y);
}


void SplashState::onEnter()
{

}

void SplashState::onExit()
{

}

void SplashState::onPushed()
{

}

void SplashState::onPopped()
{

}