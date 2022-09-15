/***************************************************************************************************************************/
/* Life.cpp
/***************************************************************************************************************************/

#include "Life.h"

// Constructor
Life::Life(sf::Texture* texture, sf::Vector2f position)
{
	PRINT("Life constructor");
	active = true;
	type = EntityType::NORMAL;
	set_sprite(texture);
	set_scale(sprite_scale_factor);
	set_position(position);
}
