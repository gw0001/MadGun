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
 * MENU SCENE - scene_menu.cpp
 *
 * Main menu for MadGun.
 *
 * Currently populated with boilerplate
 * platformer code from practicals
 */

// Libraries
#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

// Load Function
//
// Function loads required entities for the menu scene
void MenuScene::Load() 
{
	// Output menu load message to console
	cout << "Menu Load \n";
	{
		// Text entity
		auto txt = makeEntity();

		// Add Text component
		auto t = txt->addComponent<TextComponent>("MADGUN: GEARS AND BLOOD\nPress Space to Start");
	}

	// Set loaded to true
	setLoaded(true);
}

// Update Function
//
// Function updates the menu scene
void MenuScene::Update(const double& dt) 
{
	// Output menu update to the console - Will cause FPS to drop when enabled
	//cout << "Menu Update "<<dt<<"\n";

	// Check if user presses Space bar
	if (sf::Keyboard::isKeyPressed(Keyboard::Space)) 
	{
		// Change scene to Level 1
		Engine::ChangeScene(&level1);
	}

	// Update the scene
	Scene::Update(dt);
}
