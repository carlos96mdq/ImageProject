#pragma once

#include "Movable.h"
#include "Shooter.h"

class Player : public Movable, public Shooter
{
private:
	void movement(float delta_time);
	void shooting();
	void timers(float delta_time);
public:
	Player(sf::Texture* texture);
	virtual ~Player() {};
	virtual void update(float delta_time) override;
};

