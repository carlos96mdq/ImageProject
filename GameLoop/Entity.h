/***************************************************************************************************************************/
/* Entity.h
/* Defines and entity ingame. Any object ingame is an entity.
/***************************************************************************************************************************/

#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "GlobalMethods.h"

// Entity is used as a base class, as any object is an entity but and object derived from an entity
class Entity
{
protected:
	unsigned int id;
	EntityType type;
	bool active;
	bool alive;
public:
	Entity() { id = 0; type = EntityType::NORMAL; active = false; alive = true; };
	virtual ~Entity() {};
	void assign_id(unsigned int new_id) { id = new_id; };
	void active_entity(bool is_active) { active = is_active; };
	void kill_entity() {alive = false;};
	const unsigned int get_id() const { return id; };
	const EntityType get_type() const { return type; };
	const bool is_active() const { return active; }
	const bool is_alive() const { return alive; }
	virtual bool update(float delta_time)=0;
};

