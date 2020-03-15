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
 * ACTOR MOVEMENT COMPONENT
 * - cmp_actor_movement.h
 *
 * Header file for actor movement 
 * component
 *
 */

// Libraries
#pragma once
#include <ecm.h>

// Namespaces
using namespace std; // Standard namespace
using namespace sf; // SFML namespace

/*
 * ACTOR MOVEMENT COMPONENT CLASS
 */
class ActorMovementComponent : public Component 
{
	protected:
		// Valid Move function
		bool validMove(const Vector2f&);

		// Speed variable
		float _speed;

	public:
		// Update function
		void update(double dt) override;

		// Move function
		void move(const Vector2f&);

		// Move function
		void move(float x, float y);

		// Render function
		void render() override {};

		// Actor Movement Component contstructor
		explicit ActorMovementComponent(Entity* p);

		// Actor Movement Component deconstructor
		ActorMovementComponent() = delete;
};
