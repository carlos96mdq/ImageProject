#pragma once

#include "Movable.h"

class PlayerBullet : public Movable
{
protected:
	virtual void set_sprite(sf::Texture* texture) override;
	virtual void sprite_frame();
	virtual void timers(float delta_time);
public:
	PlayerBullet(sf::Texture* texture, sf::Vector2f position);
	virtual ~PlayerBullet() { PRINT("Bullet destructor"); };
	virtual bool update(float delta_time) override;
};

