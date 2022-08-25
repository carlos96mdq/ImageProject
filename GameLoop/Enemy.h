#pragma once

#include "Movable.h"

class Enemy : public Movable
{
private:
	sf::Vector2f direction;
	unsigned int movement_state;
	float movement_timer;
	void movement(float deltaTime);
	void shooting();
	void timers(float deltaTime);
public:
	Enemy(sf::Texture* texture);
	virtual ~Enemy() {};
	virtual void update(float deltaTime) override;
};
