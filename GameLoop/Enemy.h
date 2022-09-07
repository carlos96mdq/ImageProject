#pragma once

#include "Movable.h"
#include "Shooter.h"

class Enemy : public Movable, public Shooter
{
protected:
	unsigned int enemy_type;
	sf::Vector2f direction;
	unsigned int state;
	float state_timer;
	virtual void movement(float delta_time)=0;
	virtual void sprite_frame()=0;
	virtual void shooting()=0;
	virtual void timers(float delta_time)=0;
public:
	Enemy(sf::Texture* texture, sf::Vector2f* position, unsigned int pattern=0);
	virtual ~Enemy() {};
};
