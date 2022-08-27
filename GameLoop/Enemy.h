#pragma once

#include "Movable.h"
#include "Shooter.h"

class Enemy : public Movable, public Shooter
{
private:
	sf::Vector2f direction;
	unsigned int movement_state;
	float movement_timer;
	void movement(float delta_time);
	void shooting();
	void timers(float delta_time);
public:
	Enemy(sf::Texture* texture, sf::Vector2f* position);
	virtual ~Enemy() {};
	virtual void update(float delta_time) override;
};
