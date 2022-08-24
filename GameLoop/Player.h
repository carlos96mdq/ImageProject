#pragma once

#include "Movable.h"

class Player : public Movable
{
private:
	bool shoot;
	bool can_shoot;
	sf::Vector2f shooting_position;
	float shoot_timer;
	float shoot_cooldown;
	void movement(float deltaTime);
	void shooting();
	void timers(float deltaTime);
public:
	Player(sf::Texture* texture);
	virtual ~Player() {};
	virtual void update(float deltaTime) override;
	void already_shot() {shoot = false;};
	bool is_shooting() {return shoot;}
	sf::Vector2f get_shooting_position() {return sf::Vector2f(shooting_position);}
};

