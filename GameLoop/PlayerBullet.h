#pragma once

#include "Movable.h"

class PlayerBullet : public Movable
{
public:
	PlayerBullet(sf::Texture* texture, sf::Vector2f position);
	virtual ~PlayerBullet() { PRINT("Bullet destructor"); };
	virtual bool update(float delta_time) override;
};

