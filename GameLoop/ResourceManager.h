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
	sf::Texture* get_texture(std::string texture_name);
	bool load_textures();
	int get_count();
	void clear();
};