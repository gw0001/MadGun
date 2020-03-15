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
 * LEVEL 2 SCENE - scene_level2.cpp
 *
 * Header file of Level 2.
 *
 * Currently populated with boilerplate
 * platformer code from practicals
 */

// Libraries
#pragma once
#include "engine.h"

// Name Spaces
using namespace std; // Standard namespace
using namespace sf; // SFML namespace

/*
 * LEVEL 2 SCENE CLASS
 */
class Level2Scene : public Scene 
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