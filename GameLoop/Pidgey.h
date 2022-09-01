#pragma once

#include "Enemy.h"

class Pidgey : public Enemy
{
private:
	virtual void movement(float delta_time) override;
	virtual void sprite_frame() override;
	virtual void shooting() override;
	virtual void timers(float delta_time) override;
public:
	Pidgey(sf::Texture* texture, sf::Vector2f* position, unsigned int pattern=0);
	virtual ~Pidgey() {};
	virtual void update(float delta_time) override;
};
