/***************************************************************************************************************************/
/* Background.h
/* Level background sprite
/***************************************************************************************************************************/

#pragma once

#include "Movable.h"

class Background : public Movable
{
private:
	sf::Vector2f direction;
public:
	Background(sf::Texture* texture, sf::Vector2f position);
	~Background() {PRINT("Background destructor")};
	virtual void set_position(sf::Vector2f new_position);
	virtual bool update(float delta_time) override;
};

