#include "PlayerBullet.h"

PlayerBullet::PlayerBullet(sf::Texture* texture)
{
	set_texture(*texture);
	speed = -500;
	type = EntityType::PLAYER_BULLET;
	sprite.setPosition(400, 500);
}

void PlayerBullet::update(float deltaTime)
{
	// Move enemy in a patron
	sprite.move(0, speed * deltaTime);
}