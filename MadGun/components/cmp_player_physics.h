/*
 * GAMES ENGINEERING - COURSEWORK
 * -------------------------------------
 * MadGun: Gears and Blood
 * -------------------------------------
 * Franceso Fico - 40404272
 * Graeme White - 40415739
 * -------------------------------------
 * Code Author(s): G. White
 * Date Created: 14/03/2020
 * Date Last Modified: 15/03/2020
 * -------------------------------------
 * PLAYER PHYSICS COMPONET
 * - cmp_player_physics.h
 *
 * Header file for player physics
 * component
 *
 * Currently populated with boiler plate
 * code from platformer practical
 *
 */

// Libraries
#pragma once
#include "cmp_physics.h"

// Namespaces
using namespace std; // Standard namespace
using namespace sf; // SFML namespace


/*
 * PLAYER PHYSICS COMPONENT CLASS
 */
class PlayerPhysicsComponent : public PhysicsComponent 
{
	protected:
		// Size vector
		b2Vec2 _size;

		// Maximum Veloctity
		Vector2f _maxVelocity;

		// Grounded Boolean
		bool _grounded;

		// Ground Speed
		float _groundspeed;

		// Is Grounded Function
		bool isGrounded() const;

	public:
		// Update function
		void update(double dt) override;

		// Player Physics Component constructor
		explicit PlayerPhysicsComponent(Entity* p, const Vector2f& size);

		// Player Physics Component deconstructor
		PlayerPhysicsComponent() = delete;
};
