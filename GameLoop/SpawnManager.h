#pragma once

#include <queue>
#include <list>
#include "Constants.h"
#include "Entity.h"

class SpawnManager
{
private:
	static SpawnManager* instance;
	static std::queue<sf::Vector2f*> enemies_to_spawn;
	SpawnManager();
	virtual ~SpawnManager() {};
	float enemy_spawn_timer;
	unsigned int enemy_spawn_event;
	bool enemy_spawner_flag;
	void enemy_spawner();
	void timers_update(float delta_time);
public:
	static SpawnManager* get_instance();
	static std::queue<sf::Vector2f*> get_enemies();
	void update(float delta_time);
	void enemy_already_spawned() {enemy_spawner_flag = false;};
	const bool get_enemy_spawner_flag() {return enemy_spawner_flag;};
	void clear_enemies();

	// Entity* get_entity(unsigned int id);
	// unsigned int add_entity(Entity* entity);
	// void remove_entity(unsigned int id);
	// int get_count();
	// void clear();
};

