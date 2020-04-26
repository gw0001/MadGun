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
 * ENEMY TURRET COMPONENT
 * - cmp_enemy_ai.h
 *
 * Header file for enemy turret
 * component
 *
 *
 */

// Libraries
#pragma once
#include "cmp_physics.h"
#include <ecm.h>

// Namespaces
using namespace std; // Standard namespace
using namespace sf; // SFML namespace

/*
 * ENEMY TURRET COMPONENT CLASS
 */
class EnemyTurretComponent : public Component 
{
	protected:
		// Fire function
		void fire() const;

		// Fire time
		float _firetime;

		// Default Fire time
		float _defaultFiretime;

	public:
		// Update function
		void update(double dt) override;

		// Render function
		void render() override {};

		// Set fire time function
		void setFireTime(float fireTime);

		// Enemy Turret Component Constructor
		explicit EnemyTurretComponent(Entity* p);

		// Enemy Turret Component deconstructor
		EnemyTurretComponent() = delete;
};
