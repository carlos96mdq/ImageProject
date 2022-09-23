/***************************************************************************************************************************/
/* ResourceManager.cpp
/***************************************************************************************************************************/

#include "ResourceManager.h"

// Static definitions
ResourceManager* ResourceManager::instance = nullptr;
std::unordered_map<std::string, sf::Texture*> ResourceManager::textures;
std::unordered_map<std::string, sf::Font*> ResourceManager::fonts;
std::unordered_map<std::string, sf::Music*> ResourceManager::musics;

// Singleton initialization
ResourceManager* ResourceManager::get_instance()
{
	if(instance == nullptr)
	{
		instance = new ResourceManager();
	}
	return instance;
}

// Get map container with all textures loaded inside
std::unordered_map<std::string, sf::Texture*> ResourceManager::get_textures()
{
	return textures;
}

// Get map container with all fonts loaded inside
std::unordered_map<std::string, sf::Font*> ResourceManager::get_fonts()
{
	return fonts;
}

// Get map container with all musics loaded inside
std::unordered_map<std::string, sf::Music*> ResourceManager::get_musics()
{
	return musics;
}

// Load in graphic memory all the game textures
bool ResourceManager::load_textures()
{
	bool correct_init {true};
	sf::Texture* temp_texture {};

	temp_texture = new sf::Texture;
	if (!temp_texture->loadFromFile("resources/player_sprite.png"))
	{
		std::cout << "ERROR" << std::endl;
		correct_init = false;
	}
	else
	{
		textures.emplace("player_sprite", temp_texture);
	}
	
	temp_texture = new sf::Texture;
	if (!temp_texture->loadFromFile("resources/thunderbolt_sprite.png"))
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
	
	temp_texture = new sf::Texture;
	if (!temp_texture->loadFromFile("resources/butterfree_sprite.png"))
	{
		std::cout << "ERROR" << std::endl;
		correct_init = false;
	}
	else
	{
		textures.emplace("butterfree_sprite", temp_texture);
	}
	
	temp_texture = new sf::Texture;
	if (!temp_texture->loadFromFile("resources/pidgeot_sprite.png"))
	{
		std::cout << "ERROR" << std::endl;
		correct_init = false;
	}
	else
	{
		textures.emplace("pidgeot_sprite", temp_texture);
	}
	
	temp_texture = new sf::Texture;
	if (!temp_texture->loadFromFile("resources/viridian_forest.png"))
	{
		std::cout << "ERROR" << std::endl;
		correct_init = false;
	}
	else
	{
		textures.emplace("viridian_forest_sprite", temp_texture);
	}
	
	temp_texture = new sf::Texture;
	if (!temp_texture->loadFromFile("resources/player_life.png"))
	{
		std::cout << "ERROR" << std::endl;
		correct_init = false;
	}
	else
	{
		textures.emplace("player_life_sprite", temp_texture);
	}
	
	temp_texture = nullptr;
	return correct_init;
}

// Load in heap memory all the game fonts
bool ResourceManager::load_fonts()
{
	bool correct_init {true};
	sf::Font* temp_font {};

	temp_font = new sf::Font;
	if (!temp_font->loadFromFile("resources/arial.ttf"))
	{
		std::cout << "ERROR" << std::endl;
		correct_init = false;
	}
	else
	{
		fonts.emplace("arial_font", temp_font);
	}
	
	temp_font = nullptr;
	return correct_init;
}

// Connect an audio class to an audio file (the music is not preloaded in memory, is read at real time)
bool ResourceManager::load_musics()
{
	bool correct_init {true};
	sf::Music* temp_music {};

	temp_music = new sf::Music;
	if (!temp_music->openFromFile("resources/main_music.ogg"))
	{
		std::cout << "ERROR" << std::endl;
		correct_init = false;
	}
	else
	{
		temp_music->setVolume(20.0);
		musics.emplace("main_music", temp_music);
	}
	
	temp_music = nullptr;
	return correct_init;
}

// Cleans all texture from memory
void ResourceManager::clear()
{
	// Clean textures
	for(auto const& texture : textures)
	{
		delete texture.second;
	}
	textures.clear();

	// Clean fonts
	for(auto const& font : fonts)
	{
		delete font.second;
	}
	fonts.clear();
}
