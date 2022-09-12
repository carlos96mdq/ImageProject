/***************************************************************************************************************************/
/* Boss.h
/* Boss derived from Enemy class
/***************************************************************************************************************************/

#pragma once

#include "Enemy.h"

enum STATES {ROTATING=0, TORNADUS, ATTACKING, RETURNING};

class Boss : public Enemy
{
protected:
	int rotation_factor;
	float degree_counter;
	float random_tornadus;
	float random_attack;
	sf::Vector2f initial_postion;
	sf::Vector2f current_position;
	sf::Vector2f current_direction;
	virtual void set_sprite(sf::Texture* texture) override;
	virtual void movement(float delta_time) override;
	virtual void sprite_frame() override;
	virtual void shooting() override;
	virtual void timers(float delta_time) override;
public:
	Boss(sf::Texture* texture, sf::Vector2f* position);
	~Boss() {PRINT("Boss destructor")};
	// virtual void set_position(sf::Vector2f new_position) override;
	virtual void update(float delta_time) override;
};

