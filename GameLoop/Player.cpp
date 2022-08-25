#include "Player.h"

Player::Player(sf::Texture* texture)
{
	set_texture(*texture);
	speed = 400;
	type = EntityType::PLAYER;
	shooting_position = sf::Vector2f(sprite.getPosition());
	shoot_cooldown = 0.5;
};

// Verify if any key of movement is being pressed and move the player accordingly
void Player::movement(float deltaTime)
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
	movement *= (speed * deltaTime);
	
	// Finally make de movement
	move(movement.x, movement.y);
}

// Verify if any key of shooting is being pressed and create a player bullet
void Player::shooting()
{
	// Get movement input key only if the player can move in that direction
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K) && can_shoot)
	{
		shoot = true;
		can_shoot = false;
		sf::FloatRect rect = sprite.getGlobalBounds();
		shooting_position = sf::Vector2f(rect.left + rect.width / 2, rect.top);
	}
}

// Increase active timers and handle timers events. All times are measured in seconds
void Player::timers(float deltaTime)
{
	if (!can_shoot)
	{
		shoot_timer += deltaTime;
		if (shoot_timer >= shoot_cooldown)
		{
			can_shoot = true;
			shoot_timer = 0;
		}
	}
}

void Player::update(float deltaTime)
{
	movement(deltaTime);
	shooting();
	timers(deltaTime);
}
