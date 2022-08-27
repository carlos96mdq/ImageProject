#pragma once

#include <iostream>
#include <list>
#include "Constants.h"
#include "EntityManager.h"
#include "ResourceManager.h"
#include "SpawnManager.h"
#include "Player.h"
#include "PlayerBullet.h"
#include "Enemy.h"
#include "EnemyBullet.h"

#define PRINT(x) std::cout << x << std::endl;

class Game
{
private:
	sf::RenderWindow window;
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