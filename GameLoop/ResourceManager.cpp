#include "ResourceManager.h"

ResourceManager* ResourceManager::instance = nullptr;
std::unordered_map<std::string, sf::Texture*> ResourceManager::textures;

ResourceManager* ResourceManager::get_instance()
{
	if(instance == nullptr)
	{
		instance = new ResourceManager();
	}
	return instance;
}

std::unordered_map<std::string, sf::Texture*> ResourceManager::get_textures()
{
	return textures;
}

sf::Texture* ResourceManager::get_texture(std::string texture_name)
{
	return textures.at(texture_name);
}

// Load in graphic memory all the game textures
bool ResourceManager::load_textures()
{
	// Create a texture in heap, load a texture from a file, and give a reference to that texture heap location to the map
	bool correct_init {true};
	sf::Texture* temp_texture {};

	temp_texture = new sf::Texture;
	if (!temp_texture->loadFromFile("resources/player.png"))
	{
		std::cout << "ERROR" << std::endl;
		correct_init = false;
	}
	else
	{
		textures.emplace("player_sprite", temp_texture);
	}
	
	temp_texture = new sf::Texture;
	if (!temp_texture->loadFromFile("resources/player_bullet.jpg"))
	{
		std::cout << "ERROR" << std::endl;
		correct_init = false;
	}
	else
	{
		textures.emplace("player_bullet_sprite", temp_texture);
	}
	
	temp_texture = new sf::Texture;
	if (!temp_texture->loadFromFile("resources/twister_sprite.png"))
	{
		std::cout << "ERROR" << std::endl;
		correct_init = false;
	}
	else
	{
		textures.emplace("twister_sprite", temp_texture);
	}
	
	temp_texture = new sf::Texture;
	if (!temp_texture->loadFromFile("resources/pidgey_sprites.png"))
	{
		std::cout << "ERROR" << std::endl;
		correct_init = false;
	}
	else
	{
		textures.emplace("pidgey_sprite", temp_texture);
	}
	
	temp_texture = new sf::Texture;
	if (!temp_texture->loadFromFile("resources/beedrill_sprite.png"))
	{
		std::cout << "ERROR" << std::endl;
		correct_init = false;
	}
	else
	{
		textures.emplace("beedrill_sprite", temp_texture);
	}
	
	temp_texture = nullptr;
	return correct_init;
}

int ResourceManager::get_count()
{
	return textures.size();
}

void ResourceManager::clear()
{
	for(auto const& texture : textures)
	{
		delete texture.second;
	}
	textures.clear();
}
