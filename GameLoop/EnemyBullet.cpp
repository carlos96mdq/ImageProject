/***************************************************************************************************************************/
/* EnemyBullet.cpp
/***************************************************************************************************************************/

#include "EnemyBullet.h"

// Constructor
EnemyBullet::EnemyBullet(sf::Texture* texture)
{
	active = true;
	speed = 350;
	type = EntityType::ENEMY_BULLET;
	state = 0;
	state_timer = 0;
	change_direction = false;
	angle_orientation = 1;
	set_sprite(texture);
}

// Set the spritesheet and the current sprite
void EnemyBullet::set_sprite(sf::Texture* texture)
{
	Sprite::set_sprite(texture);
	sprite_refresh_period = 0.1;
}

// Set a random direction to the bullet
void EnemyBullet::set_direction()
{
	float random = ((rand() % 21) - 10) / 10.0;
	direction = DIRECTIONS[DOWN] + sf::Vector2f(random, 0);
	MATH::normalize(direction);
}

// Needs to be overriden from Sprite parent class because an position change has to been done based on bullet origin
void EnemyBullet::set_position(sf::Vector2f new_position)
{
	new_position += sf::Vector2f(0, get_sprite_rect().height / 2);
	set_origin(get_sprite_rect().width / 2, get_sprite_rect().height / 2);
	Sprite::set_position(new_position);
	if (new_position.x > WINDOW_WIDTH / 2)
	{
		angle_orientation = -1;
	}
}

// Move projectile in a patron
void EnemyBullet::movement(float delta_time)
{
	if (change_direction)
	{
		switch (state)
		{
			case 0:
				direction = DIRECTIONS[NULL_DIR];
				break;
				
			case 1:
				set_direction();
				break;

			default:
				break;
		}
		change_direction = false;
	}
	// rotate 15 degrees per second
	MATH::rotate(direction, 15 * angle_orientation * delta_time);
	move(direction * speed * delta_time);
}

// Check the sprite time and entity state to change the current sprite and give a movement effect
void EnemyBullet::sprite_frame()
{
	if (change_sprite)
	{
		rotate_sprite(-30);
		change_sprite = false;
	}
}

// Increase active timers and handle timers events. All times are measured in seconds
void EnemyBullet::timers(float delta_time)
{
	sprite_timer += delta_time;
	if (sprite_timer >= sprite_refresh_period)
	{
		change_sprite = true;
		sprite_timer = 0.0;
	}

	if (state == 0)
	{
		state_timer += delta_time;
		if (state_timer > 2.5)
		{
			state = 1;
			change_direction = true;
			state_timer = 0;
		}
	}
}

// Update
void EnemyBullet::update(float delta_time)
{
	movement(delta_time);
	sprite_frame();
	timers(delta_time);
}