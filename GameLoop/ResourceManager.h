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
	ResourceManager() {};
	virtual ~ResourceManager() {};
public:
	static ResourceManager* get_instance();
	static std::unordered_map<std::string, sf::Texture*> get_textures();
	bool load_textures();
	sf::Texture* get_texture(std::string texture_name) const { return textures.at(texture_name); };
	const int get_count() const { return textures.size(); };
	void clear();
};