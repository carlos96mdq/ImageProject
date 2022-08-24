#pragma once

#include "Entity.h"

class Sprite : public Entity
{
protected:
	sf::Texture texture;
	sf::Sprite sprite;
public:
	Sprite() {};
	virtual ~Sprite() {};
	void draw(sf::RenderWindow* window);
	void set_texture(const sf::Texture &texture);
	void set_position(sf::Vector2f new_position);
	const sf::Sprite& get_sprite() const { return sprite; };
};

