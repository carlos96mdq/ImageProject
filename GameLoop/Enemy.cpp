#include "Enemy.h"

Enemy::Enemy(sf::Texture* texture, sf::Vector2f* position)
{
	active = true;
	set_position(*position);
	type = EntityType::ENEMY;
	direction = DIRECTIONS[NULL_DIR];
	state = 0;
	state_timer = 0;
	can_shoot = true;
	shooting_position = sf::Vector2f(sprite.getPosition());
	shoot_cooldown = 1;
	shoot_timer = shoot_cooldown;
}