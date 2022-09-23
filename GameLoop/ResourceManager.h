/***************************************************************************************************************************/
/* ResourceManager.h
/* External resources used in game, mainly sprites (.png), are administrated by a ResourceManager (a singleton)
/***************************************************************************************************************************/

#pragma once

#include <unordered_map>
#include "Constants.h"

class ResourceManager
{
private:
	static ResourceManager* instance;
	static std::unordered_map<std::string, sf::Texture*> textures;
	static std::unordered_map<std::string, sf::Font*> fonts;
	static std::unordered_map<std::string, sf::Music*> musics;
	ResourceManager() {};
	virtual ~ResourceManager() {};
public:
	static ResourceManager* get_instance();
	static std::unordered_map<std::string, sf::Texture*> get_textures();
	static std::unordered_map<std::string, sf::Font*> get_fonts();
	static std::unordered_map<std::string, sf::Music*> get_musics();
	bool load_textures();
	bool load_fonts();
	bool load_musics();
	sf::Texture* get_texture(std::string texture_name) const { return textures.at(texture_name); };
	sf::Font* get_font(std::string font_name) const { return fonts.at(font_name); };
	sf::Music* get_music(std::string music_name) const { return musics.at(music_name); };
	const int get_textures_count() const { return textures.size(); };
	const int get_fonts_count() const { return fonts.size(); };
	void clear();
};