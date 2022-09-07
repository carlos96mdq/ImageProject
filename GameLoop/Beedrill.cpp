#include "Beedrill.h"

Beedrill::Beedrill(sf::Texture* texture, sf::Vector2f* position, unsigned int pattern)
: Enemy(texture, position, pattern)
{
	PRINT("Beedrill constructor");
	enemy_type = BEEDRILL;
	speed = 350;
	if (get_position().x > WINDOW_WIDTH)
	{
		direction = DIRECTIONS[DOWN_LEFT];
		state = 0;
	}
	else
	{
		direction = DIRECTIONS[DOWN_RIGHT];
		state = 1;
	}
	set_sprite(texture);
}

// Set the spritesheet and the current sprite
void Beedrill::set_sprite(sf::Texture* texture)
{
	Sprite::set_sprite(texture);
	sprite_scale_factor = 2;
	// sprite_refresh_period = 0.3;
	sprite_quantities = 2;
	set_scale(sprite_scale_factor);
	sf::IntRect sprite_sheet(get_sprite_sheet_rect());
	sprites.push_back(new sf::IntRect(sprite_sheet.left, sprite_sheet.top, sprite_sheet.width / 2, sprite_sheet.height));
	sprites.push_back(new sf::IntRect(sprite_sheet.left + sprite_sheet.width / 2, sprite_sheet.top, sprite_sheet.width / 2, sprite_sheet.height));
	if (state == 0)
	{
		sprite_index = 0;
	}
	else
	{
		sprite_index = 1;
	}
	set_current_sprite(*sprites[sprite_index]);
}

// Move enemy in a patron
void Beedrill::movement(float delta_time)
{
	move(direction * speed * delta_time);
}

// Check the sprite time and entity state to change the current sprite and give a movement effect
void Beedrill::sprite_frame()
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

// Increase active timers and handle timers events. All times are measured in seconds
void Beedrill::timers(float delta_time)
{
	if (state == 0)
	{
		state_timer += delta_time;
		if (state_timer > 3.0)
		{
			state = 1;
			state_timer = 0;
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

	// if (state == 0)
	// {
	// 	sprite_timer += delta_time;
	// 	if (sprite_timer >= sprite_refresh_period)
	// 	{
	// 		change_sprite = true;
	// 		sprite_timer = 0.0;
	// 	}
	// }
	// else if (state == 1 && sprite_index != 2)
	// {
	// 	change_sprite = true;
	// 	sprite_timer = 0.0;
	// }
}

void Beedrill::update(float delta_time)
{
	movement(delta_time);
	// sprite_frame();
	// timers(delta_time);
}