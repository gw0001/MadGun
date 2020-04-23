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
 * CONTINUE SCENE - scene_continue.cpp
 *
 * Continue Scene for MadGun
 */

// Libraries
#include "scene_continue.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Window/Joystick.hpp>

// Component libraries
#include "../components/cmp_text.h"



// Load Function
//
// Function loads required entities for the continue scene
void ContinueScene::Load() 
{
	// Message to console
	cout << "Continue Load \n";

	auto e = makeEntity();

	auto txt = e->addComponent<TextComponent>("This is the Continue Scene");

	// Set camera position to the middle of the screen
	Renderer::setCameraTarget(Vector2f(gameWidth / 2, gameHeight / 2));
}

// Update Function
//
// Function updates the continue scene
void ContinueScene::Update(const double& dt) 
{
	// CODE GOES HERE
	
	
	// Update the scene
	Scene::Update(dt);
}

