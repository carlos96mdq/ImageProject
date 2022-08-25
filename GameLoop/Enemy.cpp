#include "Enemy.h"

Enemy::Enemy(sf::Texture* texture)
{
	set_texture(*texture);
	speed = 100;
	type = EntityType::ENEMY;
	direction = DIRECTIONS[DOWN_RIGHT];
	movement_state = 0;
	movement_timer = 0;
}

// Move enemy in a patron
void Enemy::movement(float deltaTime)
{
	sprite.move(direction * speed * deltaTime);
}

// Enemy shoots bullets in a patron
void Enemy::shooting()
{

}

// Increase active timers and handle timers events. All times are measured in seconds
void Enemy::timers(float deltaTime)
{
	movement_timer += deltaTime;

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
}

void Enemy::update(float deltaTime)
{
	movement(deltaTime);
	shooting();
	timers(deltaTime);
}