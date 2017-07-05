#pragma once
#include "Matrix3.h"
#include "Vector2.h"

namespace aie
{
	class Texture;
}

struct SpriteObject
{
	aie::Texture* texture;
	Vector2 position;
	Vector2 dimensions;
};
