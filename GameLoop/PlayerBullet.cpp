#include "PlayerBullet.h"

PlayerBullet::PlayerBullet(sf::Texture* texture)
{
	set_texture(*texture);
	speed = -500;
	type = EntityType::PLAYER_BULLET;
}

void PlayerBullet::update(float deltaTime)
{
	// Move enemy in a patron
	move(0, speed * deltaTime);
}