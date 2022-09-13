/***************************************************************************************************************************/
/* Boss.h
/* Boss derived from Enemy class
/***************************************************************************************************************************/

#include "Boss.h"

// Constructor
Boss::Boss(sf::Texture* texture, sf::Vector2f* position)
: Enemy(texture)
{
	PRINT("Boss constructor")
	type = EntityType::BOSS;
	enemy_type = PIDGEOT;
	speed = 150;
	life = 10;
	can_shoot = false;
	direction = DIRECTIONS[DOWN];
	rotation_factor = 1;
	degree_counter = 0.0;
	random_tornadus = (rand() % 50 + 20) / 10.0;
	random_attack = (rand() % 50 + 20) / 10.0;
	set_sprite(texture);
	set_position(*position);
	initial_postion = *position;
}

// Set the spritesheet and the current sprite
void Boss::set_sprite(sf::Texture* texture)
{
	Sprite::set_sprite(texture);
	sprite_scale_factor = 6;
	sprite_refresh_period = 0.3;
	sprite_quantities = 3;
	set_scale(sprite_scale_factor);
	sf::IntRect sprite_sheet(get_sprite_sheet_rect());
	sprites.push_back(new sf::IntRect(sprite_sheet.left, sprite_sheet.top, sprite_sheet.width / 3, sprite_sheet.height));
	sprites.push_back(new sf::IntRect(sprite_sheet.left + sprite_sheet.width / 3, sprite_sheet.top, sprite_sheet.width / 3, sprite_sheet.height));
	sprites.push_back(new sf::IntRect(sprite_sheet.left + 2 * sprite_sheet.width / 3, sprite_sheet.top, sprite_sheet.width / 3, sprite_sheet.height));
	set_current_sprite(*sprites[sprite_index]);
}

// Move boss in a patron
void Boss::movement(float delta_time)
{
	switch (state)
	{
		case ROTATING:
		{
			// Rotate the boss until reach a compelte 360 degrees rotation. In that case do the same rotation on the
			// other way around. The rotation_factor determines that way.
			float new_degrees = 80 * delta_time;
			MATH::rotate(direction, new_degrees * rotation_factor);
			degree_counter += new_degrees; 
			if (degree_counter >= 360.0)
			{
				rotation_factor = -rotation_factor;
				degree_counter = 0.0;
				// Because the degree value will no be 360.0 but 360.x, a new position set needs to be done to overcome
				// any minival desviation
				set_position(initial_postion);
			}
			break;
		}
		case TORNADUS:
		{
			// Don't move until change state again
			if (direction != DIRECTIONS[NULL_DIR])
			{
				direction = DIRECTIONS[NULL_DIR];
			}
			break;
		}
		case ATTACKING:
		{
			// Don't move until change state again
			if (direction != DIRECTIONS[DOWN])
			{
				direction = DIRECTIONS[DOWN];
			}
			break;
		}
		case RETURNING:
		{
			// Don't move until change state again
			if (direction != DIRECTIONS[UP])
			{
				direction = DIRECTIONS[UP];
			}
			break;
		}
		default:
			break;
	}
	
	move(direction * speed * delta_time);
}

// Check the sprite time and entity state to change the current sprite and give a movement effect
void Boss::sprite_frame()
{
	if (change_sprite)
	{
		if (state == ATTACKING)
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
void Boss::shooting()
{
	if (can_shoot && state == TORNADUS)
	{
		sf::FloatRect rect = sprite.getGlobalBounds();
		shooting_position = sf::Vector2f(rect.left + rect.width / 2, rect.top + rect.height);
		shoot = true;
		can_shoot = false;
	}
}

// Increase active timers and handle timers events. All times are measured in seconds
void Boss::timers(float delta_time)
{
	if (state == ROTATING)
	{
		state_timer += delta_time;
		// Boss creates tornadus to attack
		if (state_timer > random_tornadus)
		{
			state = TORNADUS;
			random_attack -= state_timer;
			state_timer = 0.0;
			can_shoot = true;
			current_direction = direction;
		}
		// Boss flying forward to bump the player
		else if (state_timer > random_attack)
		{
			state = ATTACKING;
			random_tornadus -= state_timer;
			state_timer = 0.0;
			current_position = get_position();
			current_direction = direction;
			speed = 400;
		}
	}
	else if (state == TORNADUS)
	{
		state_timer += delta_time;
		// Boss starts rotating again after a time limit
		if (state_timer > 3.0)
		{
			state = ROTATING;
			state_timer = 0.0;
			random_tornadus = (rand() % 50 + 20) / 10.0;
			direction = current_direction;
		}
	}
	else if (state == ATTACKING)
	{
		// Boss starts flying back after attacking
		if (get_position().y > WINDOW_HEIGHT)
		{
			state = RETURNING;
		}
	}
	else if (state == RETURNING)
	{
		// Boss starts rotating again after a distance is reached
		if (get_position().y < current_position.y)
		{
			state = ROTATING;
			state_timer = 0.0;
			random_attack = (rand() % 50 + 20) / 10.0;
			set_position(current_position);
			direction = current_direction;
			speed = 150;
		}
	}
	
	if (state == ROTATING || state == TORNADUS || state == RETURNING)
	{
		if (sprite_index == 2)
		{
			change_sprite = true;
			sprite_timer = 0.0;
		}
		else
		{
			sprite_timer += delta_time;
			if (sprite_timer >= sprite_refresh_period)
			{
				change_sprite = true;
				sprite_timer = 0.0;
			}
		}
	}
	else if (state == ATTACKING && sprite_index != 2)
	{
		change_sprite = true;
		sprite_timer = 0.0;
	}
}

// Receive a damage value and discount it to boss life
void Boss::do_damage(int damage)
{
	life -= damage;
}

// Update
void Boss::update(float delta_time)
{
	movement(delta_time);
	sprite_frame();
	shooting();
	timers(delta_time);
}