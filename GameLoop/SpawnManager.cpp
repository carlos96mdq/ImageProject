/***************************************************************************************************************************/
/* SpawnManager.cpp
/* Manages the enemy's spawn system, as a singleton
/***************************************************************************************************************************/

#include "SpawnManager.h"

// Static definitions
SpawnManager* SpawnManager::instance = nullptr;
std::queue<NewEnemyData*> SpawnManager::enemies_to_spawn;

// Singleton initialization
SpawnManager* SpawnManager::get_instance()
{
	if(instance == nullptr)
	{
		instance = new SpawnManager();
	}
	return instance;
}

// Gets queue container with all entities references
std::queue<NewEnemyData*> SpawnManager::get_enemies()
{
	return enemies_to_spawn;
}

// Constructor
SpawnManager::SpawnManager()
: enemy_spawn_timer(0.0), enemy_spawner_flag(false), level_index(1), level_counter(0), last_spawn(false)
{}

// Spawns enemies depending of game time, level and a random factor
void SpawnManager::enemy_spawner()
{
	if (enemy_spawn_timer >= 3.0 && !last_spawn)
	{
		switch (level_index)
		{
			case 1:
			{
				if (level_counter > 35)
				{
					enemy_spawner_flag = true;
					last_spawn = true;
					enemies_to_spawn.push(new NewEnemyData(PIDGEOT, new sf::Vector2f(WINDOW_WIDTH - WINDOW_WIDTH * 0.5, 100)));
				}
				else
				{
					unsigned short enemy_to_spawn = rand() % 5;
					enemy_spawner_flag = true;
					level_counter++;
					switch (enemy_to_spawn)
					{
						case 0:
						{
							float ran_factor = (rand() % 45 + 1) / 100.0;
							enemies_to_spawn.push(new NewEnemyData(PIDGEY, new sf::Vector2f(WINDOW_WIDTH - WINDOW_WIDTH * (0.5 + ran_factor), 20)));
							enemies_to_spawn.push(new NewEnemyData(PIDGEY, new sf::Vector2f(WINDOW_WIDTH - WINDOW_WIDTH * (0.5 - ran_factor), 20)));
							ran_factor = (rand() % 50 + 1) / 100.0;
							enemies_to_spawn.push(new NewEnemyData(BEEDRILL, new sf::Vector2f(WINDOW_WIDTH + 10, WINDOW_HEIGHT * ran_factor)));
							enemies_to_spawn.push(new NewEnemyData(BEEDRILL, new sf::Vector2f(-10, WINDOW_HEIGHT * ran_factor)));
							break;
						}
						case 1:
						{
							float ran_factor = (rand() % 45 + 1) / 100.0;
							enemies_to_spawn.push(new NewEnemyData(PIDGEY, new sf::Vector2f(WINDOW_WIDTH - WINDOW_WIDTH * (0.5 + ran_factor), 20)));
							enemies_to_spawn.push(new NewEnemyData(PIDGEY, new sf::Vector2f(WINDOW_WIDTH - WINDOW_WIDTH * (0.5 - ran_factor), 20)));
							ran_factor = (rand() % 7 + 2) / 10.0;
							enemies_to_spawn.push(new NewEnemyData(BUTTERFREE, new sf::Vector2f(WINDOW_WIDTH + 10, WINDOW_HEIGHT * ran_factor)));
							enemies_to_spawn.push(new NewEnemyData(BUTTERFREE, new sf::Vector2f(-10, WINDOW_HEIGHT * ran_factor)));
							break;
						}
						case 2:
						{
							float ran_factor = (rand() % 50 + 1) / 100.0;
							enemies_to_spawn.push(new NewEnemyData(BEEDRILL, new sf::Vector2f(WINDOW_WIDTH + 10, WINDOW_HEIGHT * ran_factor)));
							enemies_to_spawn.push(new NewEnemyData(BEEDRILL, new sf::Vector2f(-10, WINDOW_HEIGHT * ran_factor)));
							ran_factor = (rand() % 7 + 2) / 10.0;
							enemies_to_spawn.push(new NewEnemyData(BUTTERFREE, new sf::Vector2f(WINDOW_WIDTH + 10, WINDOW_HEIGHT * ran_factor)));
							enemies_to_spawn.push(new NewEnemyData(BUTTERFREE, new sf::Vector2f(-10, WINDOW_HEIGHT * ran_factor)));
							break;
						}
						case 3:
						{
							float ran_factor = (rand() % 45 + 1) / 100.0;
							enemies_to_spawn.push(new NewEnemyData(PIDGEY, new sf::Vector2f(WINDOW_WIDTH - WINDOW_WIDTH * (0.5 + ran_factor), 20)));
							enemies_to_spawn.push(new NewEnemyData(PIDGEY, new sf::Vector2f(WINDOW_WIDTH - WINDOW_WIDTH * (0.5 - ran_factor), 20)));
							enemies_to_spawn.push(new NewEnemyData(PIDGEY, new sf::Vector2f(WINDOW_WIDTH - WINDOW_WIDTH * (0.5 + ran_factor * 0.5), 20)));
							enemies_to_spawn.push(new NewEnemyData(PIDGEY, new sf::Vector2f(WINDOW_WIDTH - WINDOW_WIDTH * (0.5 - ran_factor) * 0.5, 20)));
							break;
						}
						case 4:
						{
							float ran_factor = (rand() % 50 + 1) / 100.0;
							enemies_to_spawn.push(new NewEnemyData(BEEDRILL, new sf::Vector2f(WINDOW_WIDTH + 10, WINDOW_HEIGHT * ran_factor)));
							enemies_to_spawn.push(new NewEnemyData(BEEDRILL, new sf::Vector2f(-10, WINDOW_HEIGHT * ran_factor)));
							enemies_to_spawn.push(new NewEnemyData(BEEDRILL, new sf::Vector2f(WINDOW_WIDTH + 10, WINDOW_HEIGHT * ran_factor * 0.5)));
							enemies_to_spawn.push(new NewEnemyData(BEEDRILL, new sf::Vector2f(-10, WINDOW_HEIGHT * ran_factor * 0.5)));
							break;
						}
						default:
							break;
					}
				}
			}
			default:
				break;
		}
	}
	if (enemy_spawner_flag)
	{
		enemy_spawn_timer = 0.0;
	}
	
}

// Update spawner timer
void SpawnManager::timers_update(float delta_time)
{
	enemy_spawn_timer += delta_time;
}

// Update
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