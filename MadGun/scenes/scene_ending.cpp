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
 * ENDING SCENE - scene_ending.cpp
 *
 * Ending Scene for MadGun
 */

// Libraries
#include "scene_ending.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Window/Joystick.hpp>

// Component libraries
#include "../components/cmp_text.h"


// Load Function
//
// Function loads required entities for the ending scene
void EndingScene::Load() 
{
	// Message to console
	cout << "Options Load \n";

	auto e = makeEntity();

	auto txt = e->addComponent<TextComponent>("Here is the ending scene. Good job, buddy! Ya did good!");

	// Set camera position to the middle of the screen
	Renderer::setCameraTarget(Vector2f(gameWidth / 2, gameHeight / 2));
}

// Update Function
//
// Function updates the ending scene
void EndingScene::Update(const double& dt) 
{
	// CODE GOES HERE
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		Engine::ChangeScene(&menu);
	}
	
	// Update the scene
	Scene::Update(dt);
}