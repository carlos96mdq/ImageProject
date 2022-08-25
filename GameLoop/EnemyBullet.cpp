#include "EnemyBullet.h"

EnemyBullet::EnemyBullet(sf::Texture* texture)
{
	set_texture(*texture);
	speed = 500;
	type = EntityType::ENEMY_BULLET;
}

void EnemyBullet::update(float deltaTime)
{
	// Move enemy in a patron
	move(0, speed * deltaTime);
}