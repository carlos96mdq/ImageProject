#include "Pidgey.h"

Pidgey::Pidgey(sf::Texture* texture, sf::Vector2f* position, unsigned int pattern)
: Enemy(texture, position, pattern)
{
	enemy_type = PIDGEY;
}

// Move enemy in a patron
void Pidgey::movement(float delta_time)
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
void Pidgey::sprite_frame()
{
	if (change_sprite)
	{
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
void Pidgey::shooting()
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
void Pidgey::timers(float delta_time)
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
						if (state_timer > 3.0)
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
	
	// if (!can_shoot)
	// {
	// 	shoot_timer += delta_time;
	// 	if (shoot_timer >= shoot_cooldown)
	// 	{
	// 		can_shoot = true;
	// 		shoot_timer = 0.0;
	// 	}
	// }

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

void Pidgey::update(float delta_time)
{
	movement(delta_time);
	sprite_frame();
	shooting();
	timers(delta_time);
}