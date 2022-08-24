#pragma once

#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "EntityManager.h"
#include "ResourceManager.h"
#include "Player.h"
#include "PlayerBullet.h"
#include "Enemy.h"

#define PRINT(x) std::cout << x << std::endl;

class Game
{
private:
	sf::RenderWindow window;
	void process_input();
	void update(float deltaTime);
	void shooting_events();
	void collisions();
	void destroyer();
	void render();
public:
	Game() { PRINT("Game::Game"); };
	virtual ~Game() { PRINT("Game::~Game"); };
	void init();
	void loop();
	void stop();
};