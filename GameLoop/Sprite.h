#pragma once

#include <vector>
#include "Entity.h"

class Sprite : public Entity
{
protected:
	sf::Texture texture;
	sf::Sprite sprite;
	unsigned int sprite_index;
	float sprite_timer;
	bool change_sprite;
	float sprite_scale_factor;
	float sprite_refresh_period;
	unsigned int sprite_quantities;
	std::vector<sf::IntRect*> sprites;
	virtual void set_sprite(sf::Texture* texture);
	void set_scale(float scale);
	void set_origin(float x, float y);
	void rotate_sprite(float angle);
public:
	Sprite() {};
	virtual ~Sprite();
	void draw(sf::RenderWindow* window);
	void set_texture(const sf::Texture &texture);
	virtual void set_position(sf::Vector2f new_position);
	void set_current_sprite(const sf::IntRect& new_sprite);
	const sf::FloatRect get_sprite_rect() const { return sprite.getGlobalBounds();}
	const sf::Sprite& get_sprite() const { return sprite; };
	const sf::IntRect& get_sprite_sheet_rect() const {return sprite.getTextureRect();};
};

