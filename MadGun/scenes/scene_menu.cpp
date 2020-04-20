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
 * Date Last Modified: 15/04/2020
 * -------------------------------------
 * MENU SCENE - scene_menu.cpp
 *
 * Main menu for MadGun
 */

// Libraries
#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Window/Joystick.hpp>

//Level soundtrack
sf::Music music0;

// Load Function
//
// Function loads required entities for the menu scene
void MenuScene::Load() 
{
	//open the soundtrack file and plays it
	music0.openFromFile("res/audio/music/0_menu.ogg");
	music0.play();

	// Output menu load message to console
	cout << "Menu Load \n";
	{
		// Text entity
		auto txt = makeEntity();

		// Add Text component
		auto t = txt->addComponent<TextComponent>("MADGUN: GEARS AND BLOOD\nDEBUG VERSION\nLevel 1 - Keyboard 1 or Controller A \nLevel 2 - Keyboard 2 or Controller X\nLevel 3 - Keyboard 3 or Controller Y\nDebug Room - Keyboard Space or Controller B");
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

	// Set camera to target the centre of the menu screen
	Renderer::setCameraTarget(Vector2f(gameWidth / 2.0f, gameHeight / 2.0f));

	// Check if user presses 1
	if (Keyboard::isKeyPressed(Keyboard::Num1) || sf::Joystick::isButtonPressed(0, 0))
	{
		music0.stop();
		// Change scene to Level 1
		Engine::ChangeScene(&level1);
	}

	// Check if user presses 2
	if (Keyboard::isKeyPressed(Keyboard::Num2) || sf::Joystick::isButtonPressed(0, 2))
	{
		music0.stop();
		// Change scene to Level 2
		Engine::ChangeScene(&level2);
	}

	// Check if user presses 3
	if (Keyboard::isKeyPressed(Keyboard::Num3) || sf::Joystick::isButtonPressed(0, 3))
	{
		music0.stop();
		// Change scene to Level 3
		Engine::ChangeScene(&level3);
	}

	// Check if user presses Space bar
	if (Keyboard::isKeyPressed(Keyboard::Space) || sf::Joystick::isButtonPressed(0, 1))
	{
		music0.stop();
		// Change scene to Level 1
		Engine::ChangeScene(&debugScene);
	}

	// Update the scene
	Scene::Update(dt);
}
