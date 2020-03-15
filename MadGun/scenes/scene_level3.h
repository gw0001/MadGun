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
 * LEVEL 3 SCENE - scene_level3.h
 *
 * Header file of Level 3.
 *
 * Currently populated with boilerplate
 * platformer code from practicals
 */

// Libraries
#pragma once
#include "engine.h"

// Namespaces
using namespace std; // Standard namespace
using namespace sf; // SFML namespace

/*
 * LEVEL 3 SCENE CLASS
 */
class Level3Scene : public Scene 
{
	public:
		// Load function
		void Load() override;

		// Unload function
		void UnLoad() override;

		// Update function
		void Update(const double& dt) override;

		// Render function
		void Render() override;
};