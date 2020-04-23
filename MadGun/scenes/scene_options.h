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
 * OPTIONS SCENE - scene_options.h
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
 * OPTIONS SCENE
 *
 * Options Scene Class
 */
class OptionsScene : public Scene 
{
	public:
		// Options scene constructor
		OptionsScene() = default;

		// Options scene deconstructor
		~OptionsScene() override = default;

		// Load function
		void Load() override;

		// Update function
		void Update(const double& dt) override;

	private:
		//// Menu entity array
		//shared_ptr<Entity> _menu[MAX_MENU_ITEMS];

		//// Selection Highlight function
		//void selectionHightlight(int anInt);

		//// Move Up function
		//void moveUp();

		//// Move Down function
		//void moveDown();
};
