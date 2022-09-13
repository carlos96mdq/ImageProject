/***************************************************************************************************************************/
/* Move.h
/* Any Sprite that can move
/***************************************************************************************************************************/

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
	void move(sf::Vector2f vector);
	virtual void set_position(sf::Vector2f new_position) override;
};

