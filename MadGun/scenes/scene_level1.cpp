/*
 * GAMES ENGINEERING - COURSEWORK
 * -------------------------------------
 * MadGun: Gears and Blood
 * -------------------------------------
 * Franceso Fico - 40404272
 * Graeme White - 40415739
 * -------------------------------------
 * Code Author(s): G. White, F. Fico
 * Date Created: 14/03/2020
 * Date Last Modified: 27/04/2020
 * -------------------------------------
 * LEVEL 1 SCENE - scene_level1.cpp
 *
 * Level 1 of MadGun.
 *
 */

// Libraries
#include "scene_level1.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>
#include <SFML/Audio.hpp>
#include <SFML/Window/Joystick.hpp>

//Level audio variables
sf::Music music1;
sf::SoundBuffer buffer1;
sf::Sound endLvl1;

// Load Function
//
// Function loads all of the required entities for the first
// level of the game
void Level1Scene::Load() 
{
	// Output message to console
	cout << " Scene 1 Load" << endl;

	//open the soundtrack file and plays it
	music1.openFromFile("res/audio/music/1_manifest.ogg");
	music1.play();
	music1.setLoop(true);

	// Load level 1, tile size 40.0f
	ls::loadCSVLevelFile("res/levels/level1.csv", 40.0f);

	// Have camera target the player start position
	Renderer::setCameraTarget(ls::getTilePosition(ls::findTiles(ls::START)[0]));
	
	// Populate 
	populateLevel();

	//Simulate long loading times - can be commented out when scene becomes more complex
	//this_thread::sleep_for(chrono::milliseconds(3000));

	// Output message to console when the scene has loaded
	cout << " Scene 1 Load Done" << endl;

	// Set loaded to true
	setLoaded(true);
}

// Unload function
//
// Function unloads the scene
void Level1Scene::UnLoad() 
{
	// Display message to console when unloading the scene
	cout << "Scene 1 Unload" << endl;

	// Set camera to target the player, based on their position
	Renderer::setCameraTarget(Vector2f(0.0f, 0.0f));

	// Reset the player
	player.reset();

	// Unload the level tiles
	ls::unload();

	// Unload the scene
	Scene::UnLoad();
}

// Update function
//
// Function updates entities within the scene
void Level1Scene::Update(const double& dt) 
{
	// Set the camera to target the player, based on their position
	Renderer::setCameraTarget(player->getPosition());

	// Check player is at an end tile
	if (ls::getTileAt(player->getPosition()) == ls::EXIT) 
	{
		//end level sound played
		buffer1.loadFromFile("res/audio/fx/level.wav");
		endLvl1.setBuffer(buffer1);
		endLvl1.play();

		// Change scene to level 2
		Engine::ChangeScene((Scene*)&level2);
		music1.stop();
	}
	// Else, check if player has died
	else if (!player->isAlive())
	{
		// Reload level 2
		Engine::ChangeScene((Scene*)&level1);
	}

	// Check if user has pressed the escape key or start button
	if (Keyboard::isKeyPressed(Keyboard::Escape) || (sf::Joystick::isButtonPressed(0, 7)))
	{
		// Close the window
		Engine::ChangeScene((Scene*)&menu);
		music1.stop();
	}

	// Update the scene
	Scene::Update(dt);
}

// Render function
//
// Function renders all entities
// and tiles of the scene
void Level1Scene::Render() 
{
	// Render tiles
	ls::Render(Engine::GetWindow());

	// Render the scene
	Scene::Render();
}
