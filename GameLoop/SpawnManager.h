/***************************************************************************************************************************/
/* SpawnManager.h
/* Manages the enemy's spawn system, as a singleton
/***************************************************************************************************************************/

#pragma once

#include "Constants.h"
#include "Entity.h"

// Struct to send data to Game manager about the enemy to spawn
struct NewEnemyData
{
	unsigned int type;
	sf::Vector2f* position;
	NewEnemyData(unsigned int new_type, sf::Vector2f* new_position)
	: type(new_type), position(new_position) {}
};

class SpawnManager
{
private:
	static SpawnManager* instance;
	static std::queue<NewEnemyData*> enemies_to_spawn;
	SpawnManager();
	virtual ~SpawnManager() {};
	unsigned int level_index;
	unsigned int level_counter;
	bool last_spawn;
	float enemy_spawn_timer;
	bool enemy_spawner_flag;
	void enemy_spawner();
	void timers_update(float delta_time);
public:
	static SpawnManager* get_instance();
	static std::queue<NewEnemyData*> get_enemies();
	void update(float delta_time);
	void enemy_already_spawned() { enemy_spawner_flag = false; };
	void set_level(unsigned int new_level) { level_index = new_level; };
	const bool get_enemy_spawner_flag() const {return enemy_spawner_flag;};
	void clear_enemies();
	void clear_timers();
};

