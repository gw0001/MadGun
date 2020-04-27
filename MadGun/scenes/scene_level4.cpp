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
 * LEVEL 4 SCENE - scene_level4.cpp
 *
 * Level 4 of MadGun.
 *
 */

// Library
#include "scene_level4.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <SFML/Audio.hpp>

// Player shared pointer
static shared_ptr<Entity> player;

//Level audio variables
sf::Music music4;
sf::SoundBuffer buffer4;
sf::Sound endLvl4;

// Load function
//
// Function loads assets for the scene
void Level4Scene::Load() 
{
	// Output message to console when scene is set to load
	cout << "Scene 4 Load" << endl;

	// Load level from level 4 file
	ls::loadCSVLevelFile("res/levels/level4.csv", 40.0f);

	// Have camera target the player start position
	Renderer::setCameraTarget(ls::getTilePosition(ls::findTiles(ls::START)[0]));

	//open the soundtrack file and plays it
	music4.openFromFile("res/audio/music/4_stomper.ogg");
	music4.play();
	music4.setLoop(true);

	// Populate the level with entities and wall collision physics
	populateLevel();

	//Simulate long loading times - can be commented out when scene becomes more complex
	//this_thread::sleep_for(chrono::milliseconds(3000));

	// Output message when scene loaded
	cout << " Scene 4 Load Done" << endl;

	// Set loaded to true
	setLoaded(true);
}

void Level4Scene::UnLoad() 
{
	// Output message to console when scene is unloaded
	cout << "Scene 4 UnLoad" << endl;
	
	// Reset player
	player.reset();

	// Unload tiles
	ls::unload();

	// Unload scene
	Scene::UnLoad();
}

// Update function
//
// Function updates the scene
void Level4Scene::Update(const double& dt) 
{
	// Obtain player position
	const auto playerPos = player->getPosition();

	// Set camera to target the player, based on their position
	Renderer::setCameraTarget(playerPos);

	// Check if player has reached end tile
	if (ls::getTileAt(playerPos) == ls::EXIT)
	{
		//end level sound played
		buffer4.loadFromFile("res/audio/fx/level.wav");
		endLvl4.setBuffer(buffer4);
		endLvl4.play();
		music4.stop();
		
		// Change scene to level 1
		Engine::ChangeScene((Scene*)&level5);
	} 
	// Else, check if player is dead
	else if (!player->isAlive()) 
	{
		// Restart level 4
		Engine::ChangeScene((Scene*)&level4);
	}

	// Check if user has pressed the escape key
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		music4.stop();
		// Close the window
		Engine::ChangeScene((Scene*)&menu);
	}

	// Update scene
	Scene::Update(dt);
}

// Render function
//
// Function renders entities in the scene
void Level4Scene::Render() 
{
	// Render tiles
	ls::Render(Engine::GetWindow());

	// Render scene
	Scene::Render();
}
