/***************************************************************************************************************************/
/* Life.h
/* Player lives sprite. This class does not save the player's lives data, but the player's lives sprites to show on screen
/***************************************************************************************************************************/

#pragma once

#include "Sprite.h"

class Life : public Sprite
{
public:
	Life(sf::Texture* texture, sf::Vector2f position);
	~Life() { PRINT("Life destructor") };
	virtual bool update(float delta_time) override { return false; };
};

