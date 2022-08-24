#pragma once

#include "Movable.h"

class Enemy : public Movable
{
public:
	Enemy(sf::Texture* texture);
	virtual ~Enemy() {};
	virtual void update(float deltaTime) override;
};

