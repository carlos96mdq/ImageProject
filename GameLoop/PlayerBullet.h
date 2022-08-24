#pragma once
#include "Movable.h"
class PlayerBullet : public Movable
{
public:
	PlayerBullet(sf::Texture* texture);
	virtual ~PlayerBullet() {};
	virtual void update(float deltaTime) override;
};

