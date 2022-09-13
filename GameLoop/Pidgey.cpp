/***************************************************************************************************************************/
/* Pidgey.cpp
/***************************************************************************************************************************/

#include "Pidgey.h"

// Constructor
Pidgey::Pidgey(sf::Texture* texture, sf::Vector2f* position)
: Enemy(texture)
{
	PRINT("Pidgey constructor");
	enemy_type = PIDGEY;
	speed = 500;
	change_direction = false;
	direction = DIRECTIONS[NULL_DIR];
	set_sprite(texture);
	set_position(*position);
}

// Set the spritesheet and the current sprite
void Pidgey::set_sprite(sf::Texture* texture)
{
	Sprite::set_sprite(texture);
	sprite_scale_factor = 2;
	sprite_refresh_period = 0.3;
	sprite_quantities = 3;
	set_scale(sprite_scale_factor);
	sf::IntRect sprite_sheet(get_sprite_sheet_rect());
	sprites.push_back(new sf::IntRect(sprite_sheet.left, sprite_sheet.top, sprite_sheet.width / 3, sprite_sheet.height));
	sprites.push_back(new sf::IntRect(sprite_sheet.left + sprite_sheet.width / 3, sprite_sheet.top, sprite_sheet.width / 3, sprite_sheet.height));
	sprites.push_back(new sf::IntRect(sprite_sheet.left + 2 * sprite_sheet.width / 3, sprite_sheet.top, sprite_sheet.width / 3, sprite_sheet.height));
	set_current_sprite(*sprites[sprite_index]);
}

// Move enemy in a patron
void Pidgey::movement(float delta_time)
{
	if (change_direction)
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
		change_direction = false;
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
	if (can_shoot && state == 0)
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
	if (state == 0)
	{
		state_timer += delta_time;
		if (state_timer > 3.0)
		{
			state = 1;
			state_timer = 0;
			change_direction = true;
		}
	}
	
	// state_timer += delta_time;
	// switch (pattern)
	// {
	// 	case 0:
	// 		{
	// 			switch (state)
	// 			{
	// 				case 0:
	// 				{
	// 					if (state_timer > 3.0)
	// 					{
	// 						state = 1;
	// 						state_timer = 0;
	// 					}
	// 					break;
	// 				}
	// 				// case 1:
	// 				// {
	// 				// 	if (state_timer > 0.5)
	// 				// 	{
	// 				// 		state++;
	// 				// 		state_timer = 0;
	// 				// 		direction = DIRECTIONS[DOWN_LEFT];
	// 				// 	}
	// 				// 	break;
	// 				// }
	// 				// case 2:
	// 				// {
	// 				// 	if (state_timer > 2.0)
	// 				// 	{
	// 				// 		state++;
	// 				// 		state_timer = 0;
	// 				// 		direction = DIRECTIONS[DOWN];
	// 				// 	}
	// 				// 	break;
	// 				// }
	// 				// case 3:
	// 				// {
	// 				// 	if (state_timer > 0.5)
	// 				// 	{
	// 				// 		state = 0;
	// 				// 		state_timer = 0;
	// 				// 		direction = DIRECTIONS[DOWN_RIGHT];
	// 				// 	}
	// 				// 	break;
	// 				// }
	// 				default:
	// 					break;
	// 			}
	// 			break;
	// 		}
			
	// 	default:
	// 		break;
	// }
	
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

// If needed, a true flag is returned
bool Pidgey::update(float delta_time)
{
	movement(delta_time);
	sprite_frame();
	shooting();
	timers(delta_time);
	return false;
}