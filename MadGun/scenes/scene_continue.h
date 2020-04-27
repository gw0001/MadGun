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
 * CONTINUE SCENE - scene_continue.h
 *
 * Header file of Continue scene.
 *
 */

// Libraries
#pragma once
#include "engine.h"

// Namespaces
using namespace std; // Standard namespace
using namespace sf; // SFML namespace

/*
 * CONTINUE SCENE
 *
 * Continue Scene Class
 */
class ContinueScene : public Scene 
{
	public:
		// Menu scene constructor
		ContinueScene() = default;

		// Menu scene deconstructor
		~ContinueScene() override = default;

		// Load function
		void Load() override;

		// Update function
		void Update(const double& dt) override;

	private:
		// Game title entity
		shared_ptr<Entity> _levelSelectTitle;

		// Menu entity array
		shared_ptr<Entity> _levelMenu[5];

		// Selection Highlight function
		void selectionHightlight(int anInt);

		// Move Up function
		void moveUp();

		// Move Down function
		void moveDown();
};
