#include "Sprite.h"

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

void Sprite::draw(sf::RenderWindow* window)
{
	window->draw(sprite);
}

void Sprite::rotate_sprite(float angle)
{
	sprite.rotate(angle);
}

void Sprite::set_texture(const sf::Texture &texture)
{
	sprite.setTexture(texture);
}

void Sprite::set_position(sf::Vector2f new_position)
{
	sprite.setPosition(new_position);
}

void Sprite::set_scale(float scale)
{
	sprite.setScale(scale, scale);
}

void Sprite::set_origin(float x, float y)
{
	sprite.setOrigin(x, y);
}

void Sprite::set_current_sprite(const sf::IntRect& new_sprite)
{
	sprite.setTextureRect(new_sprite);
}