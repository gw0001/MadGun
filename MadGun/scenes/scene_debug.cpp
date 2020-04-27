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
 * Date Last Modified: 27/04/2020
 * -------------------------------------
 * DEBUG SCENE - scene_debug.cpp
 *
 * Debug Level, for testing various
 * aspects of the game
 *
 */

// Libraries
#include "scene_debug.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>
#include <SFML/Window/Joystick.hpp>

// Load Function
//
// Function loads all of the required entities for the first
// level of the game
void DebugScene::Load()
{
	// Output message to console
	cout << "Load Debug Scene" << endl;

	// Load level from debug level CSV file
	ls::loadCSVLevelFile("res/levels/debugLevel.csv", 40.0f);

	// Have camera target the player start position
	Renderer::setCameraTarget(ls::getTilePosition(ls::findTiles(ls::START)[0]));

	// Automatically populate level with entities
	populateLevel();

	//Simulate long loading times - can be commented out when scene becomes more complex
	//this_thread::sleep_for(chrono::milliseconds(3000));

	// Output message to console when the scene has loaded
	cout << " Debug Scene Load Done" << endl;

	// Set loaded to true
	setLoaded(true);
}


// Unload function
//
// Function unloads the scene
void DebugScene::UnLoad()
{
	// Display message to console when unloading the scene
	cout << "Debug Unload" << endl;

	// Reset the player
	player.reset();

	// Unload the level tiles
	ls::unload();

	// Unload the scene
	Scene::UnLoad();
}

// Unload function
//
// Function unloads the scene
void DebugScene::Reset()
{
	// Display message to console when unloading the scene
	cout << "Reset" << endl;

	// Unload the scene
	DebugScene::UnLoad();

	// Load the scene
	DebugScene::Load();
}

// Update function
//
// Function updates entities within the scene
void DebugScene::Update(const double& dt)
{
	// Set camera to target the player, based on their position
	Renderer::setCameraTarget(player->getPosition());

	// Check player is at an exit tile
	if (ls::getTileAt(player->getPosition()) == ls::EXIT) 
	{
		// Change scene to level 2
		Engine::ChangeScene((Scene*)&level2);
	}
	// Else, check if player has died
	else if (!player->isAlive())
	{
		// Reload level
		Engine::ChangeScene((Scene*)&debugScene);
	}

	// Check if R key pressed
	if (Keyboard::isKeyPressed(Keyboard::R))
	{
		Reset();
	}

	// Check if user has pressed the escape key or start button
	if (Keyboard::isKeyPressed(Keyboard::Escape) || (sf::Joystick::isButtonPressed(0, 7)))
	{
		// Close the window
		Engine::ChangeScene((Scene*)&menu);
	}

	// Update the scene
	Scene::Update(dt);
}

// Render function
//
// Function renders all entities
// and tiles of the scene
void DebugScene::Render()
{
	// Render tiles
	ls::Render(Engine::GetWindow());

	// Render the scene
	Scene::Render();
}
