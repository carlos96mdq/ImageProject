/***************************************************************************************************************************/
/* Move.h
/* Any Sprite that can move
/***************************************************************************************************************************/

#include "Movable.h"

// Move using two values
void Movable::move(float x, float y)
{
	sprite.move(x, y);
}

// Move using a 2d vector
void Movable::move(sf::Vector2f vector)
{
	sprite.move(vector);
}
