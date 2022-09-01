#pragma once

#include "Constants.h"
#include "Entity.h"

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
	// static std::queue<sf::Vector2f*> enemies_to_spawn;
	static std::queue<NewEnemyData*> enemies_to_spawn;
	SpawnManager();
	virtual ~SpawnManager() {};
	unsigned int level_enemy_secuence[2];
	unsigned int enemy_spawn_index;
	float enemy_spawn_timer;
	bool enemy_spawner_flag;
	void enemy_spawner();
	void timers_update(float delta_time);
public:
	static SpawnManager* get_instance();
	static std::queue<NewEnemyData*> get_enemies();
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

