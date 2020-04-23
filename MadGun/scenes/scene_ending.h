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
 * ENDING SCENE - scene_ending.h
 *
 * Header file of Ending scene.
 *
 */

// Libraries
#pragma once
#include "engine.h"

// Namespaces
using namespace std; // Standard namespace
using namespace sf; // SFML namespace

/*
 * MENU SCENE
 *
 * Menu Scene Class
 */
class EndingScene : public Scene 
{
	public:
		// Ending scene constructor
		EndingScene() = default;

		// Ending scene deconstructor
		~EndingScene() override = default;

		// Load function
		void Load() override;

		// Update function
		void Update(const double& dt) override;
};
