/***************************************************************************************************************************/
/* Player.h
/* Entity controlled by the player. Only one exists
/***************************************************************************************************************************/

#pragma once

#include "Movable.h"
#include "Shooter.h"

class Player : public Movable, public Shooter
{
private:
	virtual void set_sprite(sf::Texture* texture) override;
	void movement(float delta_time);
	void sprite_frame();
	void shooting();
	void timers(float delta_time);
public:
	Player(sf::Texture* texture, sf::Vector2f position);
	virtual ~Player() {};
	virtual void update(float delta_time) override;
};

