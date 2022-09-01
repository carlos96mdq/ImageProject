#include "Player.h"

Player::Player(sf::Texture* texture)
{
	active = true;
	speed = 400;
	type = EntityType::PLAYER;
	shooting_position = sf::Vector2f(sprite.getPosition());
	shoot_cooldown = 0.5;
	set_sprite(texture);
};

// Set the spritesheet and the current sprite
void Player::set_sprite(sf::Texture* texture)
{
	change_sprite = false;
	sprite_scale_factor = 0.1;
	sprite_refresh_period = 0.3;
	sprite_quantities = 2;
	set_texture(*texture);
	set_scale(sprite_scale_factor);
	sf::IntRect sprite_sheet(get_sprite_sheet_rect());
	sprites.push_back(new sf::IntRect(sprite_sheet.left, sprite_sheet.top, sprite_sheet.width / 2, sprite_sheet.height));
	sprites.push_back(new sf::IntRect(sprite_sheet.left + sprite_sheet.width / 2, sprite_sheet.top, sprite_sheet.width / 2, sprite_sheet.height));
	sprite_index = 0;
	set_current_sprite(*sprites[sprite_index]);
}

// Verify if any key of movement is being pressed and move the player accordingly
void Player::movement(float delta_time)
{
	sf::Vector2f movement;
	sf::FloatRect player_rect = sprite.getGlobalBounds();
	
	// Get movement input key only if the player can move in that direction
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player_rect.left > 0)
	{
		movement.x -= 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player_rect.left + player_rect.width <= WINDOW_WIDTH)
	{
		movement.x += 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && player_rect.top > 0)
	{
		movement.y -= 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && player_rect.top + player_rect.height <= WINDOW_HEIGHT)
	{
		movement.y += 1;
	}
	
	// Normalize movement in case the character moves in diagonal
	if (movement.x != 0 && movement.y != 0)
	{
		float magnitud = sqrt(pow(movement.x, 2) + pow(movement.y, 2));
		movement /= magnitud;
	}
	
	// Multiply magnitud for speed and time factor to get the final movement value
	movement *= (speed * delta_time);
	
	// Finally make de movement
	move(movement.x, movement.y);
}

// Check the sprite time to change the current sprite and give a movement effect
void Player::sprite_frame()
{
	if (change_sprite)
	{
		std::cout << "Sprite changed" << std::endl;
		sprite_index++;
		if (sprite_index >= sprite_quantities)
		{
			sprite_index = 0;
		}
		set_current_sprite(*sprites[sprite_index]);
		change_sprite = false;
	}
}

// Verify if any key of shooting is being pressed and create a player bullet
void Player::shooting()
{
	// Get movement input key only if the player can move in that direction
	if (can_shoot && sf::Keyboard::isKeyPressed(sf::Keyboard::K))
	{
		shoot = true;
		can_shoot = false;
		sf::FloatRect rect = sprite.getGlobalBounds();
		shooting_position = sf::Vector2f(rect.left + rect.width / 2, rect.top);
	}
}

// Increase active timers and handle timers events. All times are measured in seconds
void Player::timers(float delta_time)
{
	if (!can_shoot)
	{
		shoot_timer += delta_time;
		if (shoot_timer >= shoot_cooldown)
		{
			can_shoot = true;
			shoot_timer = 0.0;
		}
	}

	sprite_timer += delta_time;
	if (sprite_timer >= sprite_refresh_period)
	{
		change_sprite = true;
		sprite_timer = 0.0;
	}
	
}

void Player::update(float delta_time)
{
	movement(delta_time);
	sprite_frame();
	shooting();
	timers(delta_time);
}
