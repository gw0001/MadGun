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
 * BULLET COMPONENT- cmp_bullet.h
 *
 * Header file for bullet component
 *
 */

// Library
#pragma once
#include "cmp_physics.h"
#include <ecm.h>

// Namespaces
using namespace std; // Standard namespace
using namespace sf; // SFML namespace

/*
 * BULLET COMPONENT CLASS
 */
class BulletComponent : public Component 
{
	protected:
		// Lifetime
		float _lifetime;

	public:
		// Update function
		void update(double dt) override;

		// Render function
		void render() override {};

		// Bullet Component constructor
		explicit BulletComponent(Entity* p, float lifetime = 3.f);

		// Bullet Component deconstructor
		BulletComponent() = delete;
};
