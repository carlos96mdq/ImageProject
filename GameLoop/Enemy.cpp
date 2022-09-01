#include "Enemy.h"

Enemy::Enemy(sf::Texture* texture, sf::Vector2f* position, unsigned int pattern)
{
	active = true;
	set_position(*position);
	speed = 100;
	type = EntityType::ENEMY;
	direction = DIRECTIONS[DOWN_RIGHT];
	state = 0;
	state_timer = 0;
	can_shoot = true;
	shooting_position = sf::Vector2f(sprite.getPosition());
	shoot_cooldown = 1;
	shoot_timer = shoot_cooldown;
	pattern = pattern;
	set_sprite(texture);
}

// Set the spritesheet and the current sprite
void Enemy::set_sprite(sf::Texture* texture)
{
	change_sprite = false;
	sprite_scale_factor = 2;
	sprite_refresh_period = 0.3;
	sprite_quantities = 3;
	set_texture(*texture);
	set_scale(sprite_scale_factor);
	sf::IntRect sprite_sheet(get_sprite_sheet_rect());
	sprites.push_back(new sf::IntRect(sprite_sheet.left, sprite_sheet.top, sprite_sheet.width / 3, sprite_sheet.height));
	sprites.push_back(new sf::IntRect(sprite_sheet.left + sprite_sheet.width / 3, sprite_sheet.top, sprite_sheet.width / 3, sprite_sheet.height));
	sprites.push_back(new sf::IntRect(sprite_sheet.left + 2 * sprite_sheet.width / 3, sprite_sheet.top, sprite_sheet.width / 3, sprite_sheet.height));
	sprite_index = 0;
	set_current_sprite(*sprites[sprite_index]);
}

// Move enemy in a patron
void Enemy::movement(float delta_time)
{
	switch (state)
	{
		case 0:
			direction = DIRECTIONS[NULL_DIR];
			break;
			
		case 1:
			direction = DIRECTIONS[DOWN];
			break;

		default:
			break;
	}
	move(direction * speed * delta_time);
}

// Check the sprite time and entity state to change the current sprite and give a movement effect
void Enemy::sprite_frame()
{
	if (change_sprite)
	{
		std::cout << "Sprite changed" << std::endl;
		if (state == 1)
		{
			sprite_index = 2;
		}
		else
		{
			sprite_index++;
			if (sprite_index >= sprite_quantities - 1)
			{
				sprite_index = 0;
			}
		}
		set_current_sprite(*sprites[sprite_index]);
		change_sprite = false;
	}
}

// Enemy shoots bullets in a patron
void Enemy::shooting()
{
	if (can_shoot && pattern == 0 && state == 0)
	{
		sf::FloatRect rect = sprite.getGlobalBounds();
		shooting_position = sf::Vector2f(rect.left + rect.width / 2, rect.top + rect.height);
		shoot = true;
		can_shoot = false;
	}
	
}

// Increase active timers and handle timers events. All times are measured in seconds
void Enemy::timers(float delta_time)
{
	state_timer += delta_time;
	switch (pattern)
	{
		case 0:
			{
				switch (state)
				{
					case 0:
					{
						if (state_timer > 2.0)
						{
							state = 1;
							state_timer = 0;
						}
						break;
					}
					// case 1:
					// {
					// 	if (state_timer > 0.5)
					// 	{
					// 		state++;
					// 		state_timer = 0;
					// 		direction = DIRECTIONS[DOWN_LEFT];
					// 	}
					// 	break;
					// }
					// case 2:
					// {
					// 	if (state_timer > 2.0)
					// 	{
					// 		state++;
					// 		state_timer = 0;
					// 		direction = DIRECTIONS[DOWN];
					// 	}
					// 	break;
					// }
					// case 3:
					// {
					// 	if (state_timer > 0.5)
					// 	{
					// 		state = 0;
					// 		state_timer = 0;
					// 		direction = DIRECTIONS[DOWN_RIGHT];
					// 	}
					// 	break;
					// }
					default:
						break;
				}
				break;
			}
			
		default:
			break;
	}
	
	if (!can_shoot)
	{
		shoot_timer += delta_time;
		if (shoot_timer >= shoot_cooldown)
		{
			can_shoot = true;
			shoot_timer = 0.0;
		}
	}

	if (state == 0)
	{
		sprite_timer += delta_time;
		if (sprite_timer >= sprite_refresh_period)
		{
			change_sprite = true;
			sprite_timer = 0.0;
		}
	}
	else if (state == 1 && sprite_index != 2)
	{
		change_sprite = true;
		sprite_timer = 0.0;
	}
}

void Enemy::update(float delta_time)
{
	movement(delta_time);
	sprite_frame();
	shooting();
	timers(delta_time);
}