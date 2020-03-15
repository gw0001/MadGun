/*
 * GAMES ENGINEERING - COURSEWORK
 * -------------------------------------
 * MadGun: Gears and Blood
 * -------------------------------------
 * Franceso Fico - 40404272
 * Graeme White - 40415739
 * -------------------------------------
 * Code Author: G. White
 * Date Created: 14/03/2020
 * Date Last Modified: 15/03/2020
 * -------------------------------------
 * ENTITY COMPONENT MANAGER
 * - ecm.cpp
 *
 * Entity component manager
 *
 */

#include "ecm.h"

/*
 * ENTITY CLASS FUNCTIONS
 *
 * Functions for the Entity class
 */

// Blank Entity constructor
//
// Sets position to 0,0, rotation to 0, 
// alive to true, visible to true and 
// for deletion to false
Entity::Entity()
	: _position({ 0, 0 }), _rotation(0), 
	_alive(true), _visible(true), scene(nullptr),
	_fordeletion(false) {};

// Entity constructor
//
// Sets position to 0,0, rotation to 0, 
// alive to true, visible to true and 
// for deletion to false
Entity::Entity(Scene* const s)
	: _position({ 0, 0 }), _rotation(0),
	_alive(true), _visible(true), scene(s),
	_fordeletion(false) {};

// Entity Deconstructor
//
// Deconstructor for deleting Entity
Entity::~Entity()
{
	// Components can inter-depend on each other, so deleting them may take
	// multiple passes. We Keep deleting components until we can't delete any
	// more
	int deli = 0;
	while (deli != _components.size()) 
	{
		// Set deli to the size of the component vector
		deli = _components.size();

		// Erase component from vector
		_components.erase(remove_if(_components.begin(), _components.end(), [](auto& sp) { return (sp.use_count() <= 1); }), _components.end());
	}

	// Check if components vector still has components
	if (_components.size() > 0) 
	{
		// Component found, throw run time error message
		throw std::runtime_error("Can't delete entity, someone is grabbing a component!");
	}

	// Clear components vector
	_components.clear();
}

// Add tag function
//
// Function adds a tag to the entity
void Entity::addTag(const std::string& t) 
{ 
	_tags.insert(t); 
}

// Get Tags function
//
// Function retuns the tags of an entity
const std::set<std::string>& Entity::getTags() const 
{ 
	return _tags; 
}

// Update Function
//
// Function for rendering each entity
void Entity::update(const double dt)
{
	// Check if entity is alive
	if (_alive == false)
	{
		// Entity is not alive, return
		return;
	}

	// Iterate over all components held in component vector
	for (size_t i = 0; i < _components.size(); i++) 
	{
		// Check if entity has been marked for deletion
		if (_components[i]->is_fordeletion()) 
		{
			// Entity marked for deletion, remove from the component vector
			_components.erase(_components.begin() + i);

			// Decrement i to previous position
			--i;
		}

		// Update component at element i
		_components[i]->update(dt);
	}
}

// Render Function
//
// Function for updating each entity
void Entity::render()
{
	// Check if entity is visible
	if (_visible == false)
	{
		// Entity not visible, return
		return;
	}

	// Iterate over all components held in component vector
	for (auto c : _components)
	{
		// Render component
		c->render();
	}
}

 // Get Position Function
 //
 // Function returns the position of the entity
const Vector2f &Entity::getPosition() const
{ 
	return Entity::_position;
}

// Set Position Function
//
// Function sets the position of the entity
void Entity::setPosition(const Vector2f &_position) 
{
	Entity::_position = _position;
}

// Is For Deletion check
//
// Function for checking if the entity is marked for deletion
bool Entity::is_fordeletion() const
{
	return Entity::_fordeletion;
}

// Get Rotation Function
//
// Funtion return the rotation of the entity
float Entity::getRotation() const
{
	return Entity::_rotation;
}

// Set Rotation Function
//
// Function sets the rotation of the entity
void Entity::setRotation(float _rotation)
{
	Entity::_rotation = _rotation;
}

// Is Alive Check
//
// Function to check if the entity is alive
bool Entity::isAlive() const
{
	return Entity::_alive;
}

// Set Alive function
//
// Function to set the entity's alive value
void Entity::setAlive(bool _alive)
{
	Entity::_alive = _alive;
}

// Set For Delete function
//
// Function to mark an entity for deletion
void Entity::setForDelete()
{
	// Mark for deletion
	Entity::_fordeletion = true;

	// Entity no longer alive
	Entity::_alive = false;

	// Entity no longer visible
	Entity::_visible = false;
}

// Is Visible Check
//
// Function to check the visiblity of an entity
bool Entity::isVisible() const
{
	return Entity::_visible;
}

// Set Visible function
//
// Function to set the entity's visibility
void Entity::setVisible(bool _visible)
{
	Entity::_visible = _visible;
}

// #################################################################### //

/*
 * COMPONENT CLASS FUNCTIONS
 *
 * Functions for the Component class
 */

// Component Constructor
//
// Constructor sets the parent of the component
// and sets for deletion to false
Component::Component(Entity * const p)
	: _parent(p), _fordeletion(false) {}

// Component deconstructor
//
// For deleting component
Component::~Component()
{
}

// Is For Deletion function
//
// Function for checking if the component is marked for deletion
bool Component::is_fordeletion() const
{
	return Component::_fordeletion;
}

// #################################################################### //

/*
 * ENTITY MANAGER FUNCTIONS
 *
 * Functions for the Entity class
 */

 // Update Function
 //
 // Function updates entities in the Entity Manager struct
void EntityManager::update(double dt)
{
	// Iterate over all entities in the list
	for (size_t i = 0; i < list.size(); i++)
	{
		// Check if entity has been flagged for deletion
		if (list[i]->is_fordeletion() == true)
		{
			// Entity flagged for deletion, remove from the list vector
			list.erase(list.begin() + i);
			
			// Decrement i
			--i;
		}

		// Check if Entity is alive
		if(list[i]->_alive == true)
		{
			// Update the entity
			list[i]->update(dt);
		}
	}
}

// Render function
//
// Function renders entities to the window
void EntityManager::render()
{
	// Iterate over all entities within the entity list
	for (auto entity : list)
	{
		// Render window
		entity->render();
	}
}

// Find function
//
// Function to find an entity, based on a specified tag
vector<shared_ptr<Entity>> EntityManager::find(const string& tag) const 
{
	// Emtpy vector of shared pointer Entities for returning
	vector<shared_ptr<Entity>> ret;

	// Iterate over all entities held in entity list
	for (auto& e : list) 
	{
		// Obtain entity that matches tag
		const auto tgs = e->_tags;
		
		// Check
		if (tgs.find(tag) != tgs.end()) 
		{
			// Tagged entity found, add entity to the vector
			ret.push_back(e);
		}
	}

	// Retrun entities matching the specified tag
	return ret;
}

// Find function
//
// Function to find an entity, based on a specified tags. 
// Overriden form of previous function
vector<shared_ptr<Entity>> EntityManager::find(const vector<string>& tags) const 
{
	// Emtpy vector of shared pointer Entities for returning
	vector<shared_ptr<Entity>> ret;

	// Iterate over all 
	for (auto& e : list) 
	{
		// Obtain entity that matches tags
		const auto tgs = e->_tags;

		// Check
		if (any_of(tags.begin(), tags.end(), [&tgs](auto t) { return tgs.find(t) != tgs.end(); })) 
		{
			// Add entity to return vector
			ret.push_back(e);
		}
	}

	// Return entities matching the specified tags
	return ret;
}