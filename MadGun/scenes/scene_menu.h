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
 * MENU SCENE - scene_menu.h
 *
 * Header file Main menu.
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
 * MENU SCENE
 *
 * Menu Scene Class
 */
class MenuScene : public Scene 
{
	public:
		// Menu scene constructor
		MenuScene() = default;

		// Menu scene deconstructor
		~MenuScene() override = default;

		// Load function
		void Load() override;

		// Update function
		void Update(const double& dt) override;
};
