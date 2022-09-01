#include "Sprite.h"

Sprite::~Sprite()
{
	// Free heap memory
	for (auto &&sprite : sprites)
	{
		delete sprite;
	}
}

void Sprite::draw(sf::RenderWindow* window)
{
	window->draw(sprite);
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

void Sprite::set_current_sprite(const sf::IntRect& new_sprite)
{
	sprite.setTextureRect(new_sprite);
}