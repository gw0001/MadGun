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
 * CREDITS SCENE - scene_credits.cpp
 *
 * Credits Scene for MadGun
 */

// Libraries
#include "scene_credits.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Window/Joystick.hpp>

// Component libraries
#include "../components/cmp_text.h"

float creditsTimer = 0.0f;

float creditsDuration = 2.0f;


// Load Function
//
// Function loads required entities for the menu scene
void CreditsScene::Load() 
{
	// Message to console
	cout << "Options Load \n";

	auto e = makeEntity();

	auto txt = e->addComponent<TextComponent>("This is where the credits for the game will go");

	// Set camera position to the middle of the screen
	Renderer::setCameraTarget(Vector2f(gameWidth / 2, gameHeight / 2));
}

// Update Function
//
// Function updates the menu scene
void CreditsScene::Update(const double& dt) 
{
	// CODE GOES HERE
	if (creditsTimer < creditsDuration)
	{
		creditsTimer += dt;
	}


	if (creditsTimer >= creditsDuration)
	{
		Engine::ChangeScene(&menu);
	}
	
	// Update the scene
	Scene::Update(dt);
}