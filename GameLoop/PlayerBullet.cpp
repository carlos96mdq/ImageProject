#include "PlayerBullet.h"

PlayerBullet::PlayerBullet(sf::Texture* texture, sf::Vector2f position)
{
	PRINT("Bullet constructor");
	active = true;
	speed = -400;
	type = EntityType::PLAYER_BULLET;
	set_sprite(texture);
	set_position(position);
}

// Set the spritesheet and the current sprite
void PlayerBullet::set_sprite(sf::Texture* texture)
{
	Sprite::set_sprite(texture);
	sprite_scale_factor = 1;
	sprite_refresh_period = 0.2;
	sprite_quantities = 4;
	set_scale(sprite_scale_factor);
	sf::IntRect sprite_sheet(get_sprite_sheet_rect());
	sprites.push_back(new sf::IntRect(sprite_sheet.left, sprite_sheet.top, sprite_sheet.width / 4, sprite_sheet.height));
	sprites.push_back(new sf::IntRect(sprite_sheet.left + sprite_sheet.width / 4, sprite_sheet.top, sprite_sheet.width / 4, sprite_sheet.height));
	sprites.push_back(new sf::IntRect(sprite_sheet.left + 2 * sprite_sheet.width / 4, sprite_sheet.top, sprite_sheet.width / 4, sprite_sheet.height));
	sprites.push_back(new sf::IntRect(sprite_sheet.left + 3 * sprite_sheet.width / 4, sprite_sheet.top, sprite_sheet.width / 4, sprite_sheet.height));
	set_current_sprite(*sprites[sprite_index]);
}

// Check the sprite time and entity state to change the current sprite and give a movement effect
void PlayerBullet::sprite_frame()
{
	if (change_sprite)
	{
		sprite_index++;
		if (sprite_index >= 4)
		{
			sprite_index = 0;
		}
		set_current_sprite(*sprites[sprite_index]);
		change_sprite = false;
	}
}

// Increase active timers and handle timers events. All times are measured in seconds
void PlayerBullet::timers(float delta_time)
{
	sprite_timer += delta_time;
	if (sprite_timer >= sprite_refresh_period)
	{
		change_sprite = true;
		sprite_timer = 0.0;
	}
}

// If needed, a true flag is returned
bool PlayerBullet::update(float delta_time)
{
	move(0, speed * delta_time);
	sprite_frame();
	timers(delta_time);
	return false;
}