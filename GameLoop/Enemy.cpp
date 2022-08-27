#include "Enemy.h"

Enemy::Enemy(sf::Texture* texture, sf::Vector2f* position)
{
	active = true;
	set_texture(*texture);
	set_position(*position);
	speed = 100;
	type = EntityType::ENEMY;
	direction = DIRECTIONS[DOWN_RIGHT];
	movement_state = 0;
	movement_timer = 0;
	shooting_position = sf::Vector2f(sprite.getPosition());
	shoot_cooldown = 0.5;
}

// Move enemy in a patron
void Enemy::movement(float delta_time)
{
	move(direction * speed * delta_time);
}

// Enemy shoots bullets in a patron
void Enemy::shooting()
{

}

// Increase active timers and handle timers events. All times are measured in seconds
void Enemy::timers(float delta_time)
{
	movement_timer += delta_time;
	switch (movement_state)
	{
		case 0:
		{
			if (movement_timer > 2.0)
			{
				movement_state++;
				movement_timer = 0;
				direction = DIRECTIONS[DOWN];
			}
			break;
		}
		case 1:
		{
			if (movement_timer > 0.5)
			{
				movement_state++;
				movement_timer = 0;
				direction = DIRECTIONS[DOWN_LEFT];
			}
			break;
		}
		case 2:
		{
			if (movement_timer > 2.0)
			{
				movement_state++;
				movement_timer = 0;
				direction = DIRECTIONS[DOWN];
			}
			break;
		}
		case 3:
		{
			if (movement_timer > 0.5)
			{
				movement_state = 0;
				movement_timer = 0;
				direction = DIRECTIONS[DOWN_RIGHT];
			}
			break;
		}
		default:
			movement_state = 0;
			break;
	}
	
	if (can_shoot)
	{
		shoot_timer += delta_time;
		if (shoot_timer >= shoot_cooldown)
		{
			shoot = true;
			shoot_timer = 0;
			sf::FloatRect rect = sprite.getGlobalBounds();
			shooting_position = sf::Vector2f(rect.left + rect.width / 2, rect.top + rect.height);
		}
	}
}

void Enemy::update(float delta_time)
{
	movement(delta_time);
	shooting();
	timers(delta_time);
}