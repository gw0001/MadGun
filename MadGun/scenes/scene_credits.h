/*
 * GAMES ENGINEERING - COURSEWORK
 * -------------------------------------
 * MadGun: Gears and Blood
 * -------------------------------------
 * Franceso Fico - 40404272
 * Graeme White - 40415739
 * -------------------------------------
 * Code Author(s): G. White
 * Date Created: 23/04/2020
 * Date Last Modified: 23/04/2020
 * -------------------------------------
 * CREDITS SCENE - scene_credits.h
 *
 * Header file of Credits scene.
 *
 */

// Libraries
#pragma once
#include "engine.h"

// Namespaces
using namespace std; // Standard namespace
using namespace sf; // SFML namespace

/*
 * CREDITS SCENE
 *
 * Credits Scene Class
 */
class CreditsScene : public Scene 
{
	public:
		// Credits scene constructor
		CreditsScene() = default;

		// Credits scene deconstructor
		~CreditsScene() override = default;

		// Load function
		void Load() override;

		// Update function
		void Update(const double& dt) override;
};
