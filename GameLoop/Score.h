/***************************************************************************************************************************/
/* Score.h
/* Player score text. This class does not save the player's score data, but the player's score text to show on screen
/***************************************************************************************************************************/

#pragma once

#include "Text.h"

class Score : public Text
{
public:
	Score(sf::Font* font, unsigned int score, sf::Vector2f position);
	~Score() { PRINT("Score destructor") };
	virtual bool update(float delta_time) override { return false; };
	void set_score(unsigned int new_score);
};

