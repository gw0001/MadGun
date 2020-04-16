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
 * Date Last Modified: 13/04/2020
 * -------------------------------------
 * LEVEL 1 SCENE - scene_level1.h
 *
 * Header file of Debug Scene
 *
 */

// Libraries
#pragma once
#include "engine.h"
#include "system_renderer.h"

// Name Spaces
using namespace std; // Standard namespace
using namespace sf; // SFML namespace

/*
 * LEVEL 1 SCENE CLASS
 */
class DebugScene : public Scene 
{
	public:
		// Load function
		void Load() override;

		// Unload function
		void UnLoad() override;

		// Reset function
		void Reset();

		// Update function
		void Update(const double& dt) override;

		// Render function
		void Render() override;
};
