#include "Enemy.h"

Enemy::Enemy(sf::Texture* texture, sf::Vector2f* position, unsigned int pattern)
{
	active = true;
	set_position(*position);
	speed = 100;
	type = EntityType::ENEMY;
	direction = DIRECTIONS[NULL_DIR];
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