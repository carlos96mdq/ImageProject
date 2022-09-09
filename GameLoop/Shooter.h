/***************************************************************************************************************************/
/* Move.h
/* Any Entity which can shoot proyectiles
/***************************************************************************************************************************/

#pragma once

#include <SFML/System/Vector2.hpp>

class Shooter
{
protected:
	bool shoot;
	bool can_shoot;
	float shoot_timer;
	float shoot_cooldown;
	sf::Vector2f shooting_position;
public:
	Shooter() { shoot = false; can_shoot = true; shoot_timer = 0; shoot_cooldown = 1; };
	virtual ~Shooter() {};
	void already_shot() { shoot = false; };
	const bool is_shooting() const { return shoot; }
	const sf::Vector2f get_shooting_position() const { return sf::Vector2f(shooting_position); }
};

