/***************************************************************************************************************************/
/* Beedrill.h
/* Enemy derived from Enemy class
/***************************************************************************************************************************/

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
	Beedrill(sf::Texture* texture, sf::Vector2f* position);
	virtual ~Beedrill() {PRINT("Beedrill destrcutor");};
	virtual bool update(float delta_time) override;
};
