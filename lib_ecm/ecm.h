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
 * - ecm.h
 *
 * Header file for entity component
 * manager
 *
 */

// Libraries
#pragma once
#include "maths.h"
#include <algorithm>
#include <memory>
#include <set>
#include <typeindex>
#include <vector>

 // Name spaces
using namespace sf; // SFML Namespace
using namespace std; // STD Namespace

// Forward declaration of classes
// Entity class
class Entity;
// Scene class
class Scene;

// #################################################################### //

/*
 * COMPONENT CLASS
 */
class Component
{
	// Entity Friend
	friend Entity;

	protected:
		// Parent of component
		Entity *const _parent;

		// For Deletion boolean
		bool _fordeletion;

		// Component Constructor
		explicit Component(Entity *const p);

	public:
		// Blank Component Constructor (deleted)
		Component() = delete;

		// Is For Deletion function
		bool is_fordeletion() const;

		// Update function
		virtual void update(double dt) = 0;

		// Render function
		virtual void render() = 0;

		// Component deconstructor
		virtual ~Component();
};

// #################################################################### //

/*
 * ENTITY MANAGER STRUCT
 */
struct EntityManager
{
	// Vector of entities
	vector<shared_ptr<Entity>> list;

	// Update function
	void update(double dt);

	// Render function
	void render();

	// Find function
	vector<shared_ptr<Entity>> find(const string& tag) const;

	// Find function (alternative)
	vector<shared_ptr<Entity>> find(const vector<string>& tags) const;
};

// #################################################################### //

/*
 * ENTITY CLASS
 */
class Entity
{
	// EntityManager friend
	friend struct EntityManager;

protected:
	// Vector of shared pointer components
	vector<shared_ptr<Component>> _components;

	// Position vector
	Vector2f _position;

	// Rotation
	float _rotation;

	// Alive boolean
	bool _alive;

	// Visible boolean
	bool _visible;

	// For Deletion variable
	bool _fordeletion;

	// Tags
	set<string> _tags;

public:
	// Add tag function
	void addTag(const string& t);

	// Get tags
	const set<string>& getTags() const;

	// Scene
	Scene* const scene;

	// Blank constructor for entity
	Entity();

	// Constructor for entity
	Entity(Scene* const s);

	// Deconstructor for entity class
	virtual ~Entity();

	// Update Function
	virtual void update(const double dt);

	// Render Function
	virtual void render();

	// Get Position function
	const Vector2f &getPosition() const;

	// Set Position function
	void setPosition(const Vector2f &_position);

	// Is For Deletion function
	bool is_fordeletion() const;

	// Get Rotation Function
	float getRotation() const;

	// Set Rotation Function
	void setRotation(float _rotation);

	// Is Alive Check
	bool isAlive() const;

	// Set Alive function
	void setAlive(bool _alive);

	// Set For Delete function
	void setForDelete();

	// Is Visible Check
	bool isVisible() const;

	// Set Visible function
	void setVisible(bool _visible);

	// Add Component Template
	template <typename T, typename... Targs>
	shared_ptr<T> addComponent(Targs... params)
	{
		static_assert(is_base_of<Component, T>::value, "T != component");
		shared_ptr<T> sp(make_shared<T>(this, params...));
		_components.push_back(sp);
		return sp;
	}

	// Get Components Template
	template <typename T>
	const vector<shared_ptr<T>> get_components() const
	{
		static_assert(std::is_base_of<Component, T>::value, "T != component");
		std::vector<std::shared_ptr<T>> ret;
		for (const auto c : _components)
		{
			if (typeid(*c) == typeid(T))
			{
				ret.push_back(std::dynamic_pointer_cast<T>(c));
			}
		}
		return std::move(ret);
	}

	// Get Compatible Component Template
	// Will return a T component, or anything derived from a T component.
	template <typename T>
	const std::vector<std::shared_ptr<T>> GetCompatibleComponent()
	{
		static_assert(std::is_base_of<Component, T>::value, "T != component");
		std::vector<std::shared_ptr<T>> ret;
		for (auto c : _components)
		{
			auto dd = dynamic_cast<T*>(&(*c));
			if (dd)
			{
				ret.push_back(std::dynamic_pointer_cast<T>(c));
			}
		}
		return ret;
	}

};

// #################################################################### //
