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
 * Date Last Modified: 26/04/2020
 * -------------------------------------
 * ENEMY AI COMPONENT- cmp_enemy_ai.h
 *
 * Header file for enemy AI component
 * 
 */

// Library
#pragma once
#include "cmp_actor_movement.h"

// Namespaces
using namespace std;
using namespace sf;

/*
 * ENEMY AI COMPONENT CLASS
 */
class EnemyAIComponent : public ActorMovementComponent 
{
	protected:
		// Direction vector
		Vector2f _direction;

	public:
		// Update function
		void update(double dt) override;

		// Enemy AI Component constructor
		explicit EnemyAIComponent(Entity* p);

		// Set Speed Function
		void setSpeed(float speedVal);

		// Blank Enemy AI component Constructor (deleted)
		EnemyAIComponent() = delete;
};
