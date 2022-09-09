/***************************************************************************************************************************/
/* Pidgey.h
/* Enemy derived from Enemy class
/***************************************************************************************************************************/

#pragma once

#include "Enemy.h"

class Pidgey : public Enemy
{
private:
	bool change_direction;
	virtual void set_sprite(sf::Texture* texture) override;
	virtual void movement(float delta_time) override;
	virtual void sprite_frame() override;
	virtual void shooting() override;
	virtual void timers(float delta_time) override;
public:
	Pidgey(sf::Texture* texture, sf::Vector2f* position);
	virtual ~Pidgey() {PRINT("Pidgey destrcutor");};
	virtual void update(float delta_time) override;
};

