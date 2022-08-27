#include "PlayerBullet.h"

PlayerBullet::PlayerBullet(sf::Texture* texture)
{
	active = true;
	set_texture(*texture);
	speed = -500;
	type = EntityType::PLAYER_BULLET;
}

void PlayerBullet::update(float delta_time)
{
	// Move enemy in a patron
	move(0, speed * delta_time);
}