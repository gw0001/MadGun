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
 * LEVEL 5 SCENE - scene_level5.cpp
 *
 * Level 5 of MadGun.
 *
 */

// Library
#include "scene_level5.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <SFML/Audio.hpp>

// Player shared pointer
static shared_ptr<Entity> player;

//Level audio variables
sf::Music music5;
sf::SoundBuffer buffer5;
sf::Sound endLvl5;

// Load function
//
// Function loads assets for the scene
void Level5Scene::Load() 
{
	// Output message to console when scene is set to load
	cout << "Scene 5 Load" << endl;

	// Load level from level 3 file
	ls::loadCSVLevelFile("res/levels/level5.csv", 40.0f);

	// Have camera target the player start position
	Renderer::setCameraTarget(ls::getTilePosition(ls::findTiles(ls::START)[0]));

	//open the soundtrack file and plays it
	music5.openFromFile("res/audio/music/5_sacrifice.ogg");
	music5.play();
	music5.setLoop(true);

	// Populate the level with entities and wall collision physics
	populateLevel();

	//Simulate long loading times - can be commented out when scene becomes more complex
	//this_thread::sleep_for(chrono::milliseconds(3000));

	// Output message when scene loaded
	cout << " Scene 5 Load Done" << endl;

	// Set loaded to true
	setLoaded(true);
}

void Level5Scene::UnLoad() 
{
	// Output message to console when scene is unloaded
	cout << "Scene 5 UnLoad" << endl;
	
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
void Level5Scene::Update(const double& dt) 
{
	// Obtain player position
	const auto playerPos = player->getPosition();

	// Set camera to target the player, based on their position
	Renderer::setCameraTarget(playerPos);

	// Check if player has reached end tile
	if (ls::getTileAt(playerPos) == ls::EXIT)
	{
		//end level sound played
		buffer5.loadFromFile("res/audio/fx/level.wav");
		endLvl5.setBuffer(buffer5);
		endLvl5.play();
		music5.stop();
		
		// Change scene to credits
		Engine::ChangeScene((Scene*)&endingScene);
	} 
	// Else, check if player is dead
	else if (!player->isAlive()) 
	{
		// Restart level 3
		Engine::ChangeScene((Scene*)&level5);
	}

	// Check if user has pressed the escape key
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		music5.stop();
		// Close the window
		Engine::ChangeScene((Scene*)&menu);
	}

	// Update scene
	Scene::Update(dt);
}

// Render function
//
// Function renders entities in the scene
void Level5Scene::Render() 
{
	// Render tiles
	ls::Render(Engine::GetWindow());

	// Render scene
	Scene::Render();
}
