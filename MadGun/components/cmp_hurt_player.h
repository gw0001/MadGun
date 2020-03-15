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
 * HURT PLAYER COMPONENT
 * - cmp_hurt_player.h
 *
 * Header file for hurt player component
 *
 * Currently populated with boiler plate
 * code from platformer practical
 *
 */

// Libraries
#pragma once
#include "cmp_physics.h"
#include <ecm.h>

// Namespace
using namespace std; // Standard namesapce
using namespace sf; // SFML namespace

/*
 * HURT PLAYER COMPONENT CLASS
 */
class HurtComponent : public Component 
{
	protected:
		// Fire function (unused)
		void fire() const;

		// Player weak pointer
		weak_ptr<Entity> _player;

	public:
		// Update function
		void update(double dt) override;

		// Render function
		void render() override {};

		// Hurt Player Component constructor
		explicit HurtComponent(Entity* p);

		// Hurt Player Component deconstructor
		HurtComponent() = delete;
};
