#pragma once

#include "Enemy.h"

class Butterfree : public Enemy
{
private:
	bool change_direction;
	unsigned int initial_state;
	std::vector<float> state_times;
	// float state_times[];
	virtual void set_sprite(sf::Texture* texture) override;
	virtual void movement(float delta_time) override;
	virtual void sprite_frame() override;
	virtual void shooting() override {};
	virtual void timers(float delta_time) override;
public:
	Butterfree(sf::Texture* texture, sf::Vector2f* position, unsigned int pattern=0);
	virtual ~Butterfree() {PRINT("Butterfree destructor");};
	virtual void update(float delta_time) override;
};
