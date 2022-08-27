#include "EnemyBullet.h"

EnemyBullet::EnemyBullet(sf::Texture* texture)
{
	active = true;
	set_texture(*texture);
	speed = 500;
	type = EntityType::ENEMY_BULLET;
}

void EnemyBullet::update(float delta_time)
{
	// Move enemy in a patron
	move(0, speed * delta_time);
}