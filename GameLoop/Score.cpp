/***************************************************************************************************************************/
/* Score.cpp
/***************************************************************************************************************************/

#include "Score.h"

// Constructor
Score::Score(sf::Font* font, unsigned int score, sf::Vector2f position)
{
	PRINT("Score constructor");
	active = true;
	type = EntityType::GUI;
	set_text(font, std::to_string(score));
	set_scale(text_scale_factor);
	set_position(position);
}

// Set a new score text
void Score::set_score(unsigned int new_score)
{
	set_string(std::to_string(new_score));
}
