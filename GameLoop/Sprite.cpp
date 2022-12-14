/***************************************************************************************************************************/
/* Sprite.cpp
/***************************************************************************************************************************/

#include "Sprite.h"

// Destructor
Sprite::~Sprite()
{
	// Free heap memory
	for (auto &&sprite : sprites)
	{
		delete sprite;
	}
}

// Set the spritesheet and the current sprite
void Sprite::set_sprite(sf::Texture* texture)
{
	sprite_timer = 0.0;
	sprite_index = 0;
	change_sprite = false;
	sprite_scale_factor = 1;
	sprite_refresh_period = 0.5;
	sprite_quantities = 1;
	set_texture(*texture);
	set_scale(sprite_scale_factor);
}

// Draw sprite on screen
void Sprite::draw(sf::RenderWindow* window)
{
	window->draw(sprite);
}

// Rotate sprite
void Sprite::rotate_sprite(float angle)
{
	sprite.rotate(angle);
}

// Set textured used by the sprite
void Sprite::set_texture(const sf::Texture &texture)
{
	sprite.setTexture(texture);
}

// Set sprite position
void Sprite::set_position(sf::Vector2f new_position)
{
	sprite.setPosition(new_position);
}

// Set sprite position
void Sprite::set_position(float new_x, float new_y)
{
	sprite.setPosition(new_x, new_y);
}

// Set sprite scale, which is 1 by default
void Sprite::set_scale(float scale)
{
	sprite.setScale(scale, scale);
}

// Set sprite origin (reference to move and rotate sprite). By default, it is located at the top-left point of the sprite
void Sprite::set_origin(float x, float y)
{
	sprite.setOrigin(x, y);
}

// As the texture is a sprite sheet, a specific sprite needs to be selected
void Sprite::set_current_sprite(const sf::IntRect& new_sprite)
{
	sprite.setTextureRect(new_sprite);
}