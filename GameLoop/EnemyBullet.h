/***************************************************************************************************************************/
/* EnemyBullet.h
/* Any projectile created by an enemy
/***************************************************************************************************************************/

#pragma once

#include "Movable.h"

class EnemyBullet : public Movable
{
private:
	sf::Vector2f direction;
	bool change_direction;
	unsigned int state;
	float state_timer;
	int angle_orientation;
	virtual void set_sprite(sf::Texture* texture) override;
	void set_direction();
	void sprite_frame();
	void movement(float delta_time);
	void timers(float delta_time);
public:
	// EnemyBullet(sf::Texture* texture);
	EnemyBullet(sf::Texture* texture, sf::Vector2f position);
	virtual ~EnemyBullet() {};
	virtual void set_position(sf::Vector2f new_position) override;
	virtual bool update(float delta_time) override;
};