#include "Enemy.h"

Enemy::Enemy(sf::Texture* texture)
{
	set_texture(*texture);
	speed = 200;
	type = EntityType::ENEMY;
}

void Enemy::update(float deltaTime)
{
	// Move enemy in a patron
	sprite.move(0, speed * deltaTime);
}