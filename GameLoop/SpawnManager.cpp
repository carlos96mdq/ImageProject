#include "SpawnManager.h"

SpawnManager* SpawnManager::instance = nullptr;
std::queue<NewEnemyData*> SpawnManager::enemies_to_spawn;

SpawnManager* SpawnManager::get_instance()
{
	if(instance == nullptr)
	{
		instance = new SpawnManager();
	}
	return instance;
}

std::queue<NewEnemyData*> SpawnManager::get_enemies()
{
	return enemies_to_spawn;
}

SpawnManager::SpawnManager()
:	enemy_spawn_timer(0.0), enemy_spawner_flag(false), enemy_spawn_index(0),
	level_enemy_secuence{0, 1}
{}

void SpawnManager::enemy_spawner()
{
	switch (level_enemy_secuence[enemy_spawn_index])
	{
		case 0:
			if (enemy_spawn_timer >= 2.0)
			{
				enemy_spawner_flag = true;
				// float ran_factor = (rand() % 45 + 1) / 100.0;
				// enemies_to_spawn.push(new NewEnemyData(PIDGEY, new sf::Vector2f(WINDOW_WIDTH - WINDOW_WIDTH * (0.5 + ran_factor), 10)));
				// enemies_to_spawn.push(new NewEnemyData(PIDGEY, new sf::Vector2f(WINDOW_WIDTH - WINDOW_WIDTH * (0.5 - ran_factor), 10)));
				// float ran_factor = (rand() % 50 + 1) / 100.0;
				// PRINT(ran_factor);
				// enemies_to_spawn.push(new NewEnemyData(BEEDRILL, new sf::Vector2f(WINDOW_WIDTH + 10, WINDOW_HEIGHT * ran_factor)));
				// enemies_to_spawn.push(new NewEnemyData(BEEDRILL, new sf::Vector2f(-10, WINDOW_HEIGHT * ran_factor)));
			}
			break;
		
		case 1:
			if (enemy_spawn_timer >= 1.0)
			{
				enemy_spawner_flag = true;
				// enemies_to_spawn.push(new NewEnemyData(PIDGEY, new sf::Vector2f(WINDOW_WIDTH - WINDOW_WIDTH * 0.5, 10)));
			}
			break;
		
		default:
			break;
	}

	if (enemy_spawner_flag)
	{
		enemy_spawn_timer = 0.0;
		enemy_spawn_index++;
		if (enemy_spawn_index >= 2)
		{
			enemy_spawn_index = 0;
		}
	}
	
}

void SpawnManager::timers_update(float delta_time)
{
	enemy_spawn_timer += delta_time;
}

void SpawnManager::update(float delta_time)
{
	enemy_spawner();
	timers_update(delta_time);
}

// Clean all pointers inside the enmies queue
void SpawnManager::clear_enemies()
{
	while (!enemies_to_spawn.empty())
	{
		delete enemies_to_spawn.front()->position;
		delete enemies_to_spawn.front();
		enemies_to_spawn.pop();
	}
}