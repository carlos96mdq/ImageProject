#pragma once

#include "Movable.h"

class EnemyBullet : public Movable
{
public:
	EnemyBullet(sf::Texture* texture);
	virtual ~EnemyBullet() {};
	virtual void update(float delta_time) override;
};