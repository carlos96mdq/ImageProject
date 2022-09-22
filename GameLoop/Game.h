/***************************************************************************************************************************/
/* Game.h
/* Main manager of the game. It has references to all managers and entities, and manages the game flow
/***************************************************************************************************************************/

#pragma once

#include <iostream>
#include <list>
#include "Constants.h"
#include "EntityManager.h"
#include "ResourceManager.h"
#include "SpawnManager.h"
#include "Background.h"
#include "Player.h"
#include "PlayerBullet.h"
#include "Pidgey.h"
#include "Beedrill.h"
#include "Butterfree.h"
#include "EnemyBullet.h"
#include "Boss.h"
#include "Life.h"
#include "Score.h"

class Game
{
private:
	sf::RenderWindow window;
	unsigned int score;
	int lives;
	bool need_background_flag;
	bool score_changed_flag;
	bool player_died_flag;
	bool game_over_flag;
	bool game_paused_flag;
	int level_index;
	bool level_changed_flag;
	void process_input();
	void update(float delta_time);
	void shooting_events();
	void collision_events();
	void spawning_events();
	void destroyer();
	void render();
public:
	Game() { PRINT("Game::Game"); };
	virtual ~Game() { PRINT("Game::~Game"); };
	void init();
	void loop();
	void stop();
};