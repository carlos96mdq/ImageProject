#pragma once

#include "Movable.h"
#include "Shooter.h"

class Player : public Movable, public Shooter
{
private:
	void movement(float deltaTime);
	void shooting();
	void timers(float deltaTime);
public:
	Player(sf::Texture* texture);
	virtual ~Player() {};
	virtual void update(float deltaTime) override;
};

