#pragma once

#include <cmath>
#include <SFML/System/Vector2.hpp>
#include "Sprite.h"

class Movable : public Sprite
{
protected:
	float speed;
public:
	Movable() {};
	virtual ~Movable() {};
	void move(float x, float y);
};

