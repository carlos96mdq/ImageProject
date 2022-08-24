#include "Sprite.h"

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

