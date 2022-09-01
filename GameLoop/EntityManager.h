#pragma once

#include "Constants.h"
#include "Entity.h"

class EntityManager
{
private:
	static EntityManager* instance;
	static std::list<Entity*> entities;
	EntityManager() {};
	virtual ~EntityManager() {};
public:
	static EntityManager* get_instance();
	static std::list<Entity*> get_entities();
	Entity* get_entity(unsigned int id);
	unsigned int add_entity(Entity* entity);
	void remove_entity(unsigned int id);
	int get_count();
	void clear();
};

