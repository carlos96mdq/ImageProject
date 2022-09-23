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
			// Close window button clicked with mouse
			case sf::Event::Closed:
				window.close();
				break;
			
			// Keyboard key pressed (only one event once you press a key)
			case sf::Event::KeyPressed:
				// Pause key
				if (event.key.code == sf::Keyboard::P && level_index != 0 && !player_died_flag)
				{
					game_paused_flag = !game_paused_flag;
				}
				break;
			
			default:
				break;
		}
	}

	// Start game
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && level_index == 0)
	{
		level_index = 1;
		level_changed_flag = true;
	}
	
}

// Update all entities and managers, including player and enemies
void Game::update(float delta_time)
{
	// If player die, a timer starts to give the player a smooth transition to the level reset
	if (player_died_flag)
	{
		player_died_timer += delta_time;

		// Enemies keep moving until first timer
		if (player_died_timer >= 3.0 && !game_paused_flag)
		{
			game_paused_flag = true;
			if (game_over_flag)
			{
				EntityManager::get_instance()->add_entity(new Text(ResourceManager::get_instance()->get_font("arial_font"), "Game Over", sf::Vector2f(WINDOW_WIDTH - WINDOW_WIDTH / 2, WINDOW_HEIGHT - WINDOW_HEIGHT / 2), 2));
			}
			else
			{
				EntityManager::get_instance()->add_entity(new Text(ResourceManager::get_instance()->get_font("arial_font"), "You lose a life", sf::Vector2f(WINDOW_WIDTH - WINDOW_WIDTH / 2, WINDOW_HEIGHT - WINDOW_HEIGHT / 2), 2));
			}
		}
		// Still showing message until time limit is reached
		else if (player_died_timer >= 6.0)
		{
			level_changed_flag = true;
			player_died_flag = false;
			player_died_timer = 0.0;

			// If all lives are lost is game over and go back to main menu
			if (game_over_flag)
			{
				game_over_flag = false;
				level_index = 0;
				score = 0;
				lives = 3;
			}
		}
	}
	
	// If a new level is loaded, some things need to be cleaned
	if (level_changed_flag)
	{
		// Clear flags
		level_changed_flag = false;
		game_paused_flag = false;

		// Clean all entities ingame and ready to spawn, and set all level things
		SpawnManager::get_instance()->clear_timers();
		SpawnManager::get_instance()->clear_enemies();
		EntityManager::get_instance()->clear();
		SpawnManager::get_instance()->set_level(level_index);

		// Stop playing the game music
		ResourceManager::get_instance()->get_music("main_music")->stop();
		
		// Create level scenary
		switch (level_index)
		{
			case 0:
				EntityManager::get_instance()->add_entity(new Life(ResourceManager::get_instance()->get_texture("main_menu_sprite"), sf::Vector2f(WINDOW_WIDTH - WINDOW_WIDTH * 0.8, 0)));
				EntityManager::get_instance()->add_entity(new Text(ResourceManager::get_instance()->get_font("arial_font"), "Press Enter to start!", sf::Vector2f(WINDOW_WIDTH - WINDOW_WIDTH / 2, WINDOW_HEIGHT - WINDOW_HEIGHT * 0.3), 2));
				EntityManager::get_instance()->add_entity(new Text(ResourceManager::get_instance()->get_font("arial_font"), "Use w,a,s,d to move", sf::Vector2f(WINDOW_WIDTH - WINDOW_WIDTH / 2, WINDOW_HEIGHT - WINDOW_HEIGHT * 0.2), 1.5));
				EntityManager::get_instance()->add_entity(new Text(ResourceManager::get_instance()->get_font("arial_font"), "Use k to attack and p to pause", sf::Vector2f(WINDOW_WIDTH - WINDOW_WIDTH / 2, WINDOW_HEIGHT - WINDOW_HEIGHT * 0.15), 1.5));
				break;

			case 1:
				EntityManager::get_instance()->add_entity(new Background(ResourceManager::get_instance()->get_texture("viridian_forest_sprite"), sf::Vector2f(0, WINDOW_HEIGHT)));
				ResourceManager::get_instance()->get_music("main_music")->play();
				break;
			
			default:
				break;
		}

		if (level_index > 0)
		{
			// Create player
			EntityManager::get_instance()->add_entity(new Player(ResourceManager::get_instance()->get_texture("player_sprite"), sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2)));
		
			// Set lives in GUI
			int counter = 1;
			while (counter <= lives)
			{
				EntityManager::get_instance()->add_entity(new Life(ResourceManager::get_instance()->get_texture("player_life_sprite"), sf::Vector2f(counter * 40, WINDOW_HEIGHT - 50)));
				counter++;
			}

			// Set score in GUI
			EntityManager::get_instance()->add_entity(new Score(ResourceManager::get_instance()->get_font("arial_font"), score, sf::Vector2f(20, 20)));
		}
	}
	
	// Only do these actions if the game is unpaused
	if (!game_paused_flag)
	{
		// Verify if a new background is needed
		if (level_index > 0)
		{
			// This flag needs to be put false by a background informing that it is still there to not let any black screen
			need_background_flag = true;

			// Update SpawnManager timers and events
			SpawnManager::get_instance()->update(delta_time);
		}

		// Update all entities
		for (Entity* const& entity: EntityManager::get_entities())
		{
			if (entity->is_active())
			{
				bool flag;
				flag = entity->update(delta_time);

				// Some entities returned an active flag
				if (flag)
				{
					switch (entity->get_type())
					{
						case EntityType::BACKGROUND:
						{
							need_background_flag = false;
							break;
						}
						default:
							break;
					}
				}

				// The score needs to be updated
				if (score_changed_flag && dynamic_cast<Score*>(entity))
				{
					dynamic_cast<Score*>(entity)->set_score(score);
					score_changed_flag = false;
				}
			}
		}
	}
}

// Check if any entity has shot a bullet and create that bullet entity
void Game::shooting_events()
{
	if (level_index > 0)
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
}

// Check all the important collisions and handle the results
void Game::collision_events()
{
	if (level_index > 0)
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
								lives--;
								player_died_flag = true;
								PRINT("Player killed");
								if (lives <= 0)
								{
									game_over_flag = true;
									PRINT("Game OVer");
								}
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
								score_changed_flag = true;
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
								if (boss->get_life() <= 0)
								{
									entity->kill_entity();
									score += 20;
									score_changed_flag = true;
								}
							}
						}
					}
					break;
				}
				// Check enemy collisions
				case EntityType::BACKGROUND:
				{
					Background* background = dynamic_cast<Background*>(entity);
					if (background != nullptr)
					{
						// Check if background image gets out of screen
						if (background->get_sprite_rect().top > WINDOW_HEIGHT)
						{
							entity->kill_entity();
						}
					}
					break;
				}
				default:
					break;
			}
		}
	}
}

// Check the spawn manager for new enemies
void Game::spawning_events()
{
	if (level_index > 0)
	{
		EntityManager* entity_manager = EntityManager::get_instance();
		ResourceManager* resource_manager = ResourceManager::get_instance();
		SpawnManager* spawn_manager = SpawnManager::get_instance();
		std::queue<NewEnemyData*> enemies_to_spawn = SpawnManager::get_enemies();

		// Spawn new enemies
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

		// Spawn new background sprite
		if (need_background_flag)
		{
			entity_manager->add_entity(new Background(resource_manager->get_texture("viridian_forest_sprite"), sf::Vector2f(0, 0)));
		}
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

	// Draw the background
	for (Entity* const& entity : EntityManager::get_entities())
	{
		if (entity->is_active() && entity->get_type() == EntityType::BACKGROUND)
		{
			Sprite* sprite = dynamic_cast<Sprite*>(entity);
			if (sprite != nullptr)
			{
				sprite->draw(&window);
			}
		}
	}

	// Draw all players and npc sprites
	for (Entity* const& entity : EntityManager::get_entities())
	{
		if (entity->is_active() && entity->get_type() != EntityType::BACKGROUND && entity->get_type() != EntityType::GUI)
		{
			Sprite* sprite = dynamic_cast<Sprite*>(entity);
			if (sprite != nullptr)
			{
				sprite->draw(&window);
			}
		}
	}

	// Draw GUI elements
	for (Entity* const& entity : EntityManager::get_entities())
	{
		if (entity->is_active() && entity->get_type() == EntityType::GUI)
		{
			Sprite* sprite = dynamic_cast<Sprite*>(entity);
			if (sprite != nullptr)
			{
				sprite->draw(&window);
			}
			else
			{
				Text* text = dynamic_cast<Text*>(entity);
				if (text != nullptr)
				{
					text->draw(&window);
				}
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
	
	// Initialize score and lives
	score = 0;
	lives = 3;

	// Initialize flags
	player_died_flag = false;
	game_over_flag = false;
	game_paused_flag = false;
	score_changed_flag = false;
	need_background_flag = false;

	// Initialize timers
	player_died_timer = 0.0;

	// Set level 0 (main menu)
	level_index = 0;
	level_changed_flag = true;

	// Create game window
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pokemon Dungeon");

	// Load all game resources
	resource_manager->load_textures();
	resource_manager->load_fonts();
	resource_manager->load_musics();
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
	ResourceManager::get_instance()->clear();
}
