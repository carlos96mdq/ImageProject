/***************************************************************************************************************************/
/* Game.h
/* Main manager of the game. It has references to all managers and entities, and manages the game flow
/***************************************************************************************************************************/

#include "Game.h"

// Process all players inputs and handle them
void Game::process_input()
{
	// Create the event handler
	sf::Event event;
	// Get all the events of the event queue
	while (window.pollEvent(event))
	{
		// Handle the event
		switch (event.type)
		{
			case sf::Event::Closed:
				window.close();
				break;
			
			default:
				break;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	{
	}
}

// Update all entities and managers, including player and enemies
void Game::update(float delta_time)
{
	// Update all entities
	for (Entity* const& entity: EntityManager::get_entities())
	{
		if (entity->is_active())
		{
			entity->update(delta_time);
		}
	}
	// Update SpawnManager timers and events
	SpawnManager::get_instance()->update(delta_time);
}

// Check if any entity has shot a bullet and create that bullet entity
void Game::shooting_events()
{
	EntityManager* entity_manager = EntityManager::get_instance();
	ResourceManager* resource_manager = ResourceManager::get_instance();

	for (Entity* const& entity: EntityManager::get_entities())
	{
		if (entity->is_active())
		{
			switch (entity->get_type())
			{
				case EntityType::PLAYER:
				{
					Shooter* player = dynamic_cast<Shooter*>(entity);
					if (player != nullptr && player->is_shooting())
					{
						player->already_shot();
						entity_manager->add_entity(new PlayerBullet(resource_manager->get_texture("player_bullet_sprite"), player->get_shooting_position()));
					}
					break;
				}
				case EntityType::ENEMY:
				{
					Enemy* enemy = dynamic_cast<Enemy*>(entity);
					if (enemy != nullptr && enemy->is_shooting())
					{
						enemy->already_shot();
						if (enemy->get_type() == PIDGEY)
						{
						entity_manager->add_entity(new EnemyBullet(resource_manager->get_texture("twister_sprite"), enemy->get_shooting_position()));
						}
					}
					break;
				}
				case EntityType::BOSS:
				{
					Enemy* enemy = dynamic_cast<Enemy*>(entity);
					if (enemy != nullptr && enemy->is_shooting())
					{
						enemy->already_shot();
						if (enemy->get_type() == PIDGEOT)
						{
							entity_manager->add_entity(new EnemyBullet(resource_manager->get_texture("twister_sprite"), enemy->get_shooting_position()));
							entity_manager->add_entity(new EnemyBullet(resource_manager->get_texture("twister_sprite"), enemy->get_shooting_position() + sf::Vector2f(100.0, 0)));
							entity_manager->add_entity(new EnemyBullet(resource_manager->get_texture("twister_sprite"), enemy->get_shooting_position() + sf::Vector2f(-100.0, 0)));
						}
					}
					break;
				}
			}
		}
	}
}

// Check all the important collisions and handle the results
void Game::collision_events()
{
	std::list<Entity*> entities = EntityManager::get_entities();
	EntityManager* entity_manager = EntityManager::get_instance();
	
	for (Entity* const& entity : entities)
	{
		switch (entity->get_type())
		{
			// Check player collisions
			case EntityType::PLAYER:
			{
				Player* player = dynamic_cast<Player*>(entity);
				if (player != nullptr)
				{
					// Check player collision with other entities
					sf::FloatRect my_rect = player->get_sprite_rect();
					for (Entity* const& col_entity : entities)
					{
						if	((col_entity->get_type() == EntityType::ENEMY_BULLET
							|| col_entity->get_type() == EntityType::ENEMY
							|| col_entity->get_type() == EntityType::BOSS)
							&& dynamic_cast<Sprite*>(col_entity)->get_sprite_rect().intersects(my_rect))
						{
							entity->kill_entity();
						}
					}
				}
				break;
			}
			// Check enemy collisions
			case EntityType::ENEMY:
			{
				Enemy* enemy = dynamic_cast<Enemy*>(entity);
				if (enemy != nullptr)
				{
					// Check if enemy get out of screen
					if (enemy->get_sprite_rect().top > WINDOW_HEIGHT)
					{
						entity->kill_entity();
					}

					// Check enemy collision with other entities
					sf::FloatRect my_rect = enemy->get_sprite_rect();
					for (Entity* const& col_entity : entities)
					{
						if	(col_entity->get_type() == EntityType::PLAYER_BULLET
							&& dynamic_cast<Sprite*>(col_entity)->get_sprite_rect().intersects(my_rect))
						{
							entity->kill_entity();
							// Add enemy points to player score
							switch (enemy->get_type())
							{
								case PIDGEY:
									score += 1;
									PRINT(score);
									break;
								
								case BEEDRILL:
									score += 3;
									PRINT(score);
									break;
								
								case BUTTERFREE:
									score += 2;
									PRINT(score);
									break;
								
								default:
									break;
							}
						}
						else if	(col_entity->get_type() == EntityType::PLAYER
								&& dynamic_cast<Sprite*>(col_entity)->get_sprite_rect().intersects(my_rect))
						{
							entity->kill_entity();
						}
					}
				}
				break;
			}
			// Check player bullets collisions
			case EntityType::PLAYER_BULLET:
			{
				PlayerBullet* player_bullet = dynamic_cast<PlayerBullet*>(entity);
				if (player_bullet != nullptr)
				{
					// Check if bullet get out of screen
					if (player_bullet->get_sprite_rect().top < 0)
					{
						entity->kill_entity();
					}

					// Check bullet collision with other entities
					sf::FloatRect my_rect = player_bullet->get_sprite_rect();
					for (Entity* const& col_entity : entities)
					{
						// Collision with enemy or boss
						if	((col_entity->get_type() == EntityType::ENEMY || col_entity->get_type() == EntityType::BOSS)
							&& dynamic_cast<Sprite*>(col_entity)->get_sprite_rect().intersects(my_rect))
						{
							entity->kill_entity();
						}
					}
				}
				break;
			}
			// Check enemy bullets collisions
			case EntityType::ENEMY_BULLET:
			{
				EnemyBullet* enemy_bullet = dynamic_cast<EnemyBullet*>(entity);
				if (enemy_bullet != nullptr)
				{
					// Check if bullet get out of screen
					if (enemy_bullet->get_sprite_rect().top > WINDOW_HEIGHT || enemy_bullet->get_sprite_rect().top < 0)
					{
						entity->kill_entity();
					}

					// Check bullet collision with other entities
					sf::FloatRect my_rect = enemy_bullet->get_sprite_rect();
					for (Entity* const& col_entity : entities)
					{
						if	(col_entity->get_type() == EntityType::PLAYER
							&& dynamic_cast<Sprite*>(col_entity)->get_sprite_rect().intersects(my_rect))
						{
							entity->kill_entity();
						}
					}
				}
				break;
			}
			// Check boss collisions
			case EntityType::BOSS:
			{
				Boss* boss = dynamic_cast<Boss*>(entity);
				if (boss != nullptr)
				{
					// Check boss collision with other entities
					sf::FloatRect my_rect = boss->get_sprite_rect();
					for (Entity* const& col_entity : entities)
					{
						if	(col_entity->get_type() == EntityType::PLAYER_BULLET
							&& dynamic_cast<Sprite*>(col_entity)->get_sprite_rect().intersects(my_rect))
						{
							boss->do_damage(1);
							PRINT(boss->get_life());
							if (boss->get_life() < 0)
							{
								entity->kill_entity();
								score += 20;
								PRINT(score);
							}
						}
					}
				}
				break;
			}
			default:
				break;
		}
	}
}

// Check the spawn manager for new enemies
void Game::spawning_events()
{
	EntityManager* entity_manager = EntityManager::get_instance();
	ResourceManager* resource_manager = ResourceManager::get_instance();
	SpawnManager* spawn_manager = SpawnManager::get_instance();
	std::queue<NewEnemyData*> enemies_to_spawn = SpawnManager::get_enemies();

	if (spawn_manager->get_enemy_spawner_flag())
	{
		spawn_manager->enemy_already_spawned();

		// WHile there are enemies to spawn, spawn them
		while (!enemies_to_spawn.empty())
		{
			unsigned int enemy_type = enemies_to_spawn.front()->type;
			switch (enemy_type)
			{
				case PIDGEY:
				{
					entity_manager->add_entity(new Pidgey(resource_manager->get_texture("pidgey_sprite"), enemies_to_spawn.front()->position));
					break;
				}
				case BEEDRILL:
				{
					entity_manager->add_entity(new Beedrill(resource_manager->get_texture("beedrill_sprite"), enemies_to_spawn.front()->position));
					break;
				}
				case BUTTERFREE:
				{
					entity_manager->add_entity(new Butterfree(resource_manager->get_texture("butterfree_sprite"), enemies_to_spawn.front()->position));
					break;
				}
				case PIDGEOT:
				{
					entity_manager->add_entity(new Boss(resource_manager->get_texture("pidgeot_sprite"), enemies_to_spawn.front()->position));
					break;
				}
				default:
					break;
			}
			enemies_to_spawn.pop();
		}
		// As the enemies_to_spawn is a copy, the true queue needs to be clean
		spawn_manager->clear_enemies();
	}
}

// Destroy all entities that are marked to be destroyed
void Game::destroyer()
{
	for (Entity* const& entity: EntityManager::get_entities())
	{
		if (!entity->is_alive())
		{
			EntityManager::get_instance()->remove_entity(entity->get_id());
		}
	}
}

// Draw all objects on window
void Game::render()
{
	window.clear();
	
	for (Entity* const& entity : EntityManager::get_entities())
	{
		if (entity->is_active())
		{
			Sprite* sprite = dynamic_cast<Sprite*>(entity);
			if (sprite != nullptr)
			{
				sprite->draw(&window);
			}
		}
	}

	window.display();
}

// Initialize game windows and important entities
void Game::init()
{
	ResourceManager* resource_manager = ResourceManager::get_instance();
	EntityManager* entity_manager = EntityManager::get_instance();

	// Initialize pseudo-randomizer
	srand(time(0));
	
	// Initialize score
	score = 0;
	PRINT(score)

	// Create game window
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pokemon Dungeon");
	resource_manager->load_textures();
	entity_manager->add_entity(new Player(resource_manager->get_texture("player_sprite"), sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2)));
	// unsigned int player = entity_manager->add_entity(new Player(resource_manager->get_texture("player_sprite")));
	// dynamic_cast<Movable*>(entity_manager->get_entity(player))->move(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

// Main gameloop
void Game::loop()
{
	sf::Clock clock;
	
	// Verify if the game window still running and ejecute all the fram verifications and updates
	while (window.isOpen())
	{
		sf::Time delta_time = clock.restart();
		process_input();
		update(delta_time.asSeconds());
		shooting_events();
		collision_events();
		spawning_events();
		destroyer();
		render();
	}
}

// Called when the main gameloop finishes
void Game::stop()
{
	EntityManager::get_instance()->clear();
}
