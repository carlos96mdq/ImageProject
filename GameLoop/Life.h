/***************************************************************************************************************************/
/* Life.h
/* Player lvies sprite
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

