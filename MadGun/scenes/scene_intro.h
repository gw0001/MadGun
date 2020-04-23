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
 * INTRO SCENE - scene_intro.h
 *
 * Header file of Intro scene scene.
 *
 */

// Libraries
#pragma once
#include "engine.h"

// Namespaces
using namespace std; // Standard namespace
using namespace sf; // SFML namespace

/*
 * INTRO SCENE
 *
 * Intro Scene Class
 */
class IntroScene : public Scene 
{
	public:
		// Intro scene constructor
		IntroScene() = default;

		// Intro scene deconstructor
		~IntroScene() override = default;

		// Load function
		void Load() override;

		// Update function
		void Update(const double& dt) override;
};
