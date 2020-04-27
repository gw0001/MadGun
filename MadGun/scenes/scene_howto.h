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
 * Date Last Modified: 27/04/2020
 * -------------------------------------
 * HOW TO SCENE - scene_howto.h
 *
 * Header file of Options scene.
 *
 */

// Libraries
#pragma once
#include "engine.h"

// Namespaces
using namespace std; // Standard namespace
using namespace sf; // SFML namespace

/*
 * HOW TO SCENE
 *
 * How-To Scene Class
 */
class HowToScene : public Scene 
{
	public:
		// Options scene constructor
		HowToScene() = default;

		// Options scene deconstructor
		~HowToScene() override = default;

		// Load function
		void Load() override;

		// Update function
		void Update(const double& dt) override;
};
