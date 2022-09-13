/***************************************************************************************************************************/
/* Butterfree.cpp
/***************************************************************************************************************************/

#include "Butterfree.h"

// Constructor
Butterfree::Butterfree(sf::Texture* texture, sf::Vector2f* position)
: Enemy(texture), state_times{4.0, 2.0, 2.0}
{
	PRINT("Butterfree constructor")
	enemy_type = BUTTERFREE;
	speed = 150;
	change_direction = false;
	// Set new state time values
	float t_rand = (rand() % 10 + 1) / 10.0;
	state_times[1] += t_rand; 
	state_times[2] += t_rand; 
	set_sprite(texture);
	set_position(*position);
	if (get_position().x > WINDOW_WIDTH)
	{
		direction = DIRECTIONS[LEFT];
		state = 1;
		initial_state = 1;
	}
	else
	{
		direction = DIRECTIONS[RIGHT];
		state = 2;
		initial_state = 2;
	}
}

// Set the spritesheet and the current sprite
void Butterfree::set_sprite(sf::Texture* texture)
{
	Sprite::set_sprite(texture);
	sprite_scale_factor = 2;
	sprite_refresh_period = 0.3;
	sprite_quantities = 6;
	set_scale(sprite_scale_factor);
	sf::IntRect sprite_sheet(get_sprite_sheet_rect());
	sprites.push_back(new sf::IntRect(sprite_sheet.left, sprite_sheet.top, sprite_sheet.width / 6, sprite_sheet.height));
	sprites.push_back(new sf::IntRect(sprite_sheet.left + sprite_sheet.width / 6, sprite_sheet.top, sprite_sheet.width / 6, sprite_sheet.height));
	sprites.push_back(new sf::IntRect(sprite_sheet.left + 2 * sprite_sheet.width / 6, sprite_sheet.top, sprite_sheet.width / 6, sprite_sheet.height));
	sprites.push_back(new sf::IntRect(sprite_sheet.left + 3 * sprite_sheet.width / 6, sprite_sheet.top, sprite_sheet.width / 6, sprite_sheet.height));
	sprites.push_back(new sf::IntRect(sprite_sheet.left + 4 * sprite_sheet.width / 6, sprite_sheet.top, sprite_sheet.width / 6, sprite_sheet.height));
	sprites.push_back(new sf::IntRect(sprite_sheet.left + 5 * sprite_sheet.width / 6, sprite_sheet.top, sprite_sheet.width / 6, sprite_sheet.height));
	if (state == 1)
	{
		sprite_index = 2;
	}
	else
	{
		sprite_index = 4;
	}
	set_current_sprite(*sprites[sprite_index]);
}

// Move enemy in a patron
void Butterfree::movement(float delta_time)
{
	if (change_direction)
	{
		switch (state)
		{
			case 0:
				direction = DIRECTIONS[NULL_DIR];
				break;
				
			case 1:
				direction = DIRECTIONS[LEFT];
				break;
				
			case 2:
				direction = DIRECTIONS[RIGHT];
				break;

			case 3:
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
void Butterfree::sprite_frame()
{
	if (change_sprite)
	{
		if (state == 0)
		{
			if (sprite_index == 0)
			{
				sprite_index = 1;
			}
			else
			{
				sprite_index = 0;
			}
		}
		else if (state == 1)
		{
			if (sprite_index == 2)
			{
				sprite_index = 3;
			}
			else
			{
				sprite_index = 2;
			}
		}
		else
		{
			if (sprite_index == 4)
			{
				sprite_index = 5;
			}
			else
			{
				sprite_index = 4;
			}
		}
		set_current_sprite(*sprites[sprite_index]);
		change_sprite = false;
	}
}

// Increase active timers and handle timers events. All times are measured in seconds
void Butterfree::timers(float delta_time)
{
	if (state != 3)
	{
		state_timer += delta_time;
		if (state == 0 && state_timer > state_times[0])
		{
			if (initial_state == 1)
			{
				state = 2;
			}
			else
			{
				state = 1;
			}
			state_timer = 0;
			change_direction = true;
		}
		else if (state == 1 && initial_state == 1 && state_timer > state_times[1]
				|| state == 2 && initial_state == 2 && state_timer > state_times[2]
				|| state == 1 && initial_state == 2 && state_timer > 2 * state_times[1]
				|| state == 2 && initial_state == 1 && state_timer > 2 * state_times[2])
		{
			if (state != initial_state)
			{
				state = 3;
			}
			else
			{
				state = 0;
			}
			state_timer = 0;
			change_direction = true;
		}
	}
	
	sprite_timer += delta_time;
	if (sprite_timer >= sprite_refresh_period)
	{
		change_sprite = true;
		sprite_timer = 0.0;
	}
}

// If needed, a true flag is returned
bool Butterfree::update(float delta_time)
{
	movement(delta_time);
	sprite_frame();
	timers(delta_time);
	return false;
}