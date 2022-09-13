#include "PlayerBullet.h"

PlayerBullet::PlayerBullet(sf::Texture* texture, sf::Vector2f position)
{
	PRINT("Bullet constructor");
	active = true;
	set_texture(*texture);
	speed = -500;
	type = EntityType::PLAYER_BULLET;
	set_position(position);
	PRINT("bullet.x: " << position.x);
	PRINT("bullet.y: " << position.y);
}

void PlayerBullet::update(float delta_time)
{
	// Move enemy in a patron
	move(0, speed * delta_time);
}