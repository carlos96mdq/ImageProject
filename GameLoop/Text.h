/***************************************************************************************************************************/
/* Text.h
/* Any Entity that needs to be write on screen using letters is a Text
/***************************************************************************************************************************/

#pragma once

#include "Entity.h"

class Text : public Entity
{
protected:
	sf::Text text;
	float text_scale_factor;
	virtual void set_text(sf::Font* font, std::string string_text);
	void set_scale(float scale);
	void set_origin(float x, float y);
	void rotate_text(float angle);
public:
	Text(sf::Font* font, std::string initial_text, sf::Vector2f position, float scale_factor=1);
	Text(sf::Font* font, unsigned int initial_text, sf::Vector2f position, float scale_factor=1);
	virtual ~Text() {};
	virtual bool update(float delta_time) override { return false; };
	void draw(sf::RenderWindow* window);
	void set_font(const sf::Font &font);
	void set_string(const std::string &new_text);
	virtual void set_position(sf::Vector2f new_position);
	virtual void set_position(float new_x, float new_y);
	const sf::Text& get_text() const { return text; };
	const sf::Vector2f& get_position() const { return text.getPosition(); }
};

