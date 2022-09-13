/***************************************************************************************************************************/
/* Enemy.h
/***************************************************************************************************************************/

#include "Enemy.h"

// Constructor. Called as a base class constrcutor by all enemies
Enemy::Enemy(sf::Texture* texture)
{
	active = true;
	type = EntityType::ENEMY;
	direction = DIRECTIONS[NULL_DIR];
	state = 0;
	state_timer = 0.0;
	can_shoot = true;
	shoot_cooldown = 1;
	shoot_timer = shoot_cooldown;
}