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
 * SYSTEM PHYSICS - system_physics.cpp
 *
 * System physics
 *
 */


// Libraries
#include "system_physics.h"

/*
 * PHYSICS NAMESPACE
 */
namespace Physics 
{
	// World
	static shared_ptr<b2World> world;

	// Velocity iterations
	const int32 velocityIterations = 6;

	// Position iterations
	const int32 positionIterations = 2;

	// Initialise function
	void initialise() 
	{
		// Set gravity to 9.81 m/s^2
		b2Vec2 gravity(0.0f, -9.81f);

		// Apply gravity to world object for simuilating rigid body physics
		world.reset(new b2World(gravity));
	}

	// Shutdown function
	//
	// Function shutsdown the physics by resetting the world
	void shutdown() 
	{ 
		// Reset world
		world.reset(); 
	}

	// Update function
	//
	// Function updates the physics of the world
	void update(const double& dt) 
	{
		// Update world
		world->Step((float)dt, velocityIterations, positionIterations);
	}

	// Get World function
	//
	// Function returns the world in use
	shared_ptr<b2World> GetWorld() 
	{ 
		return world; 
	}

	// Convert Box2D Vector to SFML Vector function
	//
	// Function converts a Box2D vector to a SFML float vector 
	const Vector2f bv2_to_sv2(const b2Vec2& in, bool scale) 
	{
		// Check if scale is true
		if (scale) 
		{
			// Return a scaled SFML vector
			return Vector2f((in.x * physics_scale), (in.y * physics_scale));
		} 
		// Else
		else 
		{
			// Return an unscaled SFML vector
			return Vector2f(in.x, in.y);
		}
	}

	// Convert SFML Vector function to Box2D Vector
	//
	// Function converts a SFML float vector to a Box2D vector
	const b2Vec2 sv2_to_bv2(const Vector2f& in, bool scale) 
	{
		// Check if scale is true
		if (scale) 
		{
			// Return scaled Box2D vector
			return b2Vec2((in.x * physics_scale_inv), (in.y * physics_scale_inv));
		} 
		// Else
		else 
		{
			// Return an unscaled Box2D vector
			return b2Vec2(in.x, in.y);
		}
	}

	// Invert Height function
	//
	// Function inverts the height
	const Vector2f invert_height(const Vector2f& in) 
	{
		// Return SFML vector with inverted height
		return Vector2f(in.x, 720 - in.y);
	}
}