/***************************************************************************************************************************/
/* Background.cpp
/***************************************************************************************************************************/

#include "Background.h"

// Constructor
Background::Background(sf::Texture* texture, sf::Vector2f position)
{
	PRINT("Background constructor");
	active = true;
	type = EntityType::BACKGROUND;
	speed = 50;
	direction = DIRECTIONS[DOWN];
	set_sprite(texture);
	sprite_scale_factor = 1.08;
	set_scale(sprite_scale_factor);
	// Sprite::set_position(0,0);
	set_position(position);
}

// Needs to be overriden from Movable parent class because the position set has to be done based on sprite down-left point
// Then the origin is set again to the top-left, so it would be easy to know when spawn the next background
void Background::set_position(sf::Vector2f new_position)
{
	set_origin(get_sprite_sheet_rect().left, get_sprite_sheet_rect().height);
	// Sprite::set_position(0, WINDOW_HEIGHT);
	Sprite::set_position(new_position.x, new_position.y);
	// set_origin(get_sprite_sheet_rect().left, get_sprite_sheet_rect().height);
}

// If needed, a true flag is returned
bool Background::update(float delta_time)
{
	// Move backgorund sprite to give a dynamic feeling
	move(direction * speed * delta_time);
	// Tell the game manager if a new background needs to be created
	if (get_sprite_rect().top >= -1)
	{
		return false;
	}
	else
	{
		return true;
	}
}