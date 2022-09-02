#include "EntityManager.h"

EntityManager* EntityManager::instance = nullptr;
std::list<Entity*> EntityManager::entities;

EntityManager* EntityManager::get_instance()
{
	if(instance == nullptr)
	{
		instance = new EntityManager();
	}
	return instance;
}

std::list<Entity*> EntityManager::get_entities()
{
	return entities;
}

Entity* EntityManager::get_entity(unsigned int id)
{
	for(auto const& entity : entities)
	{
		unsigned int entity_id = entity->get_id();
		if(entity_id == id)
		{
			return entity;
		}
	}
}

// Add a new entity to the list and assign it a new id
unsigned int EntityManager::add_entity(Entity* entity)
{
	// The id is the memory space int interpretation where the entity is pointing because it is unique and can be free easily
	unsigned int new_id = reinterpret_cast<unsigned int>(entity);
	entity->assign_id(new_id);
	entities.push_back(entity);
	return new_id;
}

void EntityManager::remove_entity(unsigned int id)
{
	for(auto entity : entities)
	{
		unsigned int entity_id = entity->get_id();
		if(entity_id == id)
		{
			delete entity;
			entities.remove(entity);
			break;
		}
	}
}

int EntityManager::get_count()
{
	return entities.size();
}

void EntityManager::clear()
{
	for(auto const& entity : entities)
	{
		delete entity;
	}
	entities.clear();
}