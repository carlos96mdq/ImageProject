/***************************************************************************************************************************/
/* EntityManager.h
/* Manages all entities, as a singleton
/***************************************************************************************************************************/

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
	Entity* get_entity(unsigned int id) const;
	unsigned int add_entity(Entity* entity);
	void remove_entity(unsigned int id);
	const int get_count() const { return entities.size(); };
	void clear();
};

