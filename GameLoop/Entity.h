#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Constants.h"

#define PRINT(x) std::cout << x << std::endl;

class Entity
{
protected:
	unsigned int id;
	EntityType type;
	bool active;
	bool alive;
public:
	Entity() { id = 0; type = EntityType::NORMAL; active = false; alive = true;};
	virtual ~Entity() {};
	void assign_id(unsigned int new_id) {id = new_id;};
	void active_entity(bool is_active) {active = is_active;};
	void kill_entity() {alive = false;};
	unsigned int get_id() const {return id;};
	EntityType get_type() const {return type;};
	bool is_active() const {return active;}
	bool is_alive() const {return alive;}
	virtual void update(float delta_time)=0;
};

