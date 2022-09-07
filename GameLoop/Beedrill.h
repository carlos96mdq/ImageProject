#pragma once

#include "Enemy.h"

class Beedrill : public Enemy
{
private:
	virtual void set_sprite(sf::Texture* texture) override;
	virtual void movement(float delta_time) override;
	virtual void sprite_frame() override;
	virtual void shooting() override {};
	virtual void timers(float delta_time) override;
public:
	Beedrill(sf::Texture* texture, sf::Vector2f* position, unsigned int pattern=0);
	virtual ~Beedrill() {PRINT("Beedrill destrcutor");};
	// virtual void set_position(sf::Vector2f new_position) override;
	virtual void update(float delta_time) override;
};
