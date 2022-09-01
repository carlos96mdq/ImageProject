#pragma once

#include "Movable.h"
#include "Shooter.h"

class Enemy : public Movable, public Shooter
{
private:
	sf::Vector2f direction;
	unsigned int enemy_type;
	unsigned int state;
	float state_timer;
	unsigned int sprite_index;
	unsigned int pattern;
	void set_sprite(sf::Texture* texture);
	void movement(float delta_time);
	void sprite_frame();
	void shooting();
	void timers(float delta_time);
public:
	Enemy(sf::Texture* texture, sf::Vector2f* position, unsigned int pattern=0);
	virtual ~Enemy() {};
	virtual void update(float delta_time) override;
};
