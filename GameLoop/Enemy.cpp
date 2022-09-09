/***************************************************************************************************************************/
/* Enemy.h
/***************************************************************************************************************************/

#include "Enemy.h"

// Constructor. Called as a base class constrcutor by all enemies
Enemy::Enemy(sf::Texture* texture, sf::Vector2f* position)
{
	active = true;
	type = EntityType::ENEMY;
	direction = DIRECTIONS[NULL_DIR];
	state = 0;
	state_timer = 0;
	can_shoot = true;
	shoot_cooldown = 1;
	shoot_timer = shoot_cooldown;
}

// Needs to be overriden from Sprite parent class because the position set has to be done based on sprite center
void Enemy::set_position(sf::Vector2f new_position)
{
	set_origin(get_sprite_sheet_rect().width / 2, get_sprite_sheet_rect().height / 2);
	Sprite::set_position(new_position);
	shooting_position = sf::Vector2f(sprite.getPosition());
}
