/***************************************************************************************************************************/
/* Text.cpp
/***************************************************************************************************************************/

#include "Text.h"

// Set the text font and size
void Text::set_text(sf::Font* font, std::string string_text)
{
	text_scale_factor = 1;
	set_font(*font);
	set_string(string_text);
	set_scale(text_scale_factor);
}

// Draw text on screen
void Text::draw(sf::RenderWindow* window)
{
	window->draw(text);
}

// Rotate text
void Text::rotate_text(float angle)
{
	text.rotate(angle);
}

// Set font used by the text
void Text::set_font(const sf::Font &font)
{
	text.setFont(font);
}

// Set string used by the text
void Text::set_string(const std::string &new_text)
{
	text.setString(new_text);
}

// Set text position
void Text::set_position(sf::Vector2f new_position)
{
	text.setPosition(new_position);
}

// Set text position
void Text::set_position(float new_x, float new_y)
{
	text.setPosition(new_x, new_y);
}

// Set text scale, which is 1 by default
void Text::set_scale(float scale)
{
	text.setScale(scale, scale);
}

// Set text origin (reference to move and rotate text). By default, it is located at the top-left point of the text
void Text::set_origin(float x, float y)
{
	text.setOrigin(x, y);
}