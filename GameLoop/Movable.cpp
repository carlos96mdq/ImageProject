#include "Movable.h"

void Movable::move(float x, float y)
{
	sprite.move(x, y);
}

void Movable::move(sf::Vector2f vector)
{
	sprite.move(vector);
}
