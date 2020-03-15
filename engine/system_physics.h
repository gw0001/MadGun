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
 * SYSTEM PHYSICS - system_physics.h
 *
 * Header file for system physics
 *
 */

// Libraries
#pragma once
#include "Box2D/Box2D.h"
#include <SFML/System/Vector2.hpp>

// Namespaces
using namespace std; // STD namespace
using namespace sf; // SFML namespace

/*
 * PHYSICS NAMESPACE
 */
namespace Physics 
{
	// Initialise function
	void initialise();

	// Shutdown function
	void shutdown();

	// Update function
	void update(const double&);

	// Get World function
	shared_ptr<b2World> GetWorld();

	// Physics Scale
	const float physics_scale = 30.0f;

	// Inverse Physics Scale
	const float physics_scale_inv = 1.0f / physics_scale;

	// Convert Box2D Vector to SFML Vector function
	const Vector2f bv2_to_sv2(const b2Vec2& in, bool scale = true);

	// Convert SFML Vector function to Box2D Vector
	const b2Vec2 sv2_to_bv2(const Vector2f& in, bool scale = true);

	// Invert Height function
	const Vector2f invert_height(const Vector2f& in);
}
