/***************************************************************************************************************************/
/* Score.cpp
/***************************************************************************************************************************/

#include "Score.h"

// Constructor
Score::Score(sf::Font* font, unsigned int score, sf::Vector2f position)
: Text(font, score, position)
{
	PRINT("Score constructor");
}

// Set a new score text
void Score::set_score(unsigned int new_score)
{
	set_string(std::to_string(new_score));
}
