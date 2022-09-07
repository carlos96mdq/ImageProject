#pragma once

#include <SFML/Graphics.hpp>
#include <queue>
#include <list>
#include <iostream>
#include <time.h>

#define PRINT(x) std::cout << x << std::endl;

const unsigned int WINDOW_WIDTH = 900;
const unsigned int WINDOW_HEIGHT = 900;

const sf::Vector2f DIRECTIONS[] = {	sf::Vector2f(0,-1), sf::Vector2f(sqrt(0.5),-sqrt(0.5)), sf::Vector2f(1,0),
									sf::Vector2f(sqrt(0.5),sqrt(0.5)), sf::Vector2f(0,1), sf::Vector2f(-sqrt(0.5),sqrt(0.5)),
									sf::Vector2f(-1,0), sf::Vector2f(-sqrt(0.5),-sqrt(0.5)), sf::Vector2f(0,0)};
enum Direction {UP=0, UP_RIGHT, RIGHT, DOWN_RIGHT, DOWN, DOWN_LEFT, LEFT, UP_LEFT, NULL_DIR};

enum class EntityType {NORMAL, PLAYER, ENEMY, PLAYER_BULLET, ENEMY_BULLET};

enum EnemyType {PIDGEY=0, BEEDRILL};