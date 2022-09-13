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

// Needs to be overriden from Sprite parent class because the position set has to be done based on sprite center
void Movable::set_position(sf::Vector2f new_position)
{
	set_origin(get_sprite_sheet_rect().width / 2, get_sprite_sheet_rect().height / 2);
	Sprite::set_position(new_position);
}

