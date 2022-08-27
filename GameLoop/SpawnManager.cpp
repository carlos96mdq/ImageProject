#include "SpawnManager.h"

SpawnManager* SpawnManager::instance = nullptr;
std::queue<sf::Vector2f*> SpawnManager::enemies_to_spawn;

SpawnManager* SpawnManager::get_instance()
{
	if(instance == nullptr)
	{
		instance = new SpawnManager();
	}
	return instance;
}

std::queue<sf::Vector2f*> SpawnManager::get_enemies()
{
	return enemies_to_spawn;
}

SpawnManager::SpawnManager()
: enemy_spawn_timer(0.0), enemy_spawn_event(0), enemy_spawner_flag(false)
{}

void SpawnManager::enemy_spawner()
{
	switch (enemy_spawn_event)
	{
		case 0:
			if (enemy_spawn_timer >= 2.0)
			{
				enemy_spawner_flag = true;
				std::cout << "Modo 1" << std::endl;
				enemies_to_spawn.push(new sf::Vector2f(WINDOW_WIDTH - WINDOW_WIDTH * 0.8, 10));
			}
			break;
		
		case 1:
			if (enemy_spawn_timer >= 3.0)
			{
				enemy_spawner_flag = true;
				std::cout << "Modo 0" << std::endl;
				enemies_to_spawn.push(new sf::Vector2f(WINDOW_WIDTH - WINDOW_WIDTH * 0.5, 10));
			}
			break;
		
		default:
			break;
	}

	if (enemy_spawner_flag)
	{
		enemy_spawn_timer = 0.0;
		enemy_spawn_event++;
		if (enemy_spawn_event >= 2)
		{
			enemy_spawn_event = 0;
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
		delete enemies_to_spawn.front();
		enemies_to_spawn.pop();
	}
}