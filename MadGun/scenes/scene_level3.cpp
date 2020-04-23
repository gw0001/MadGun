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
 * Date Last Modified: 22/04/2020
 * -------------------------------------
 * LEVEL 3 SCENE - scene_level3.cpp
 *
 * Level 3 of MadGun.
 *
 */

// Library
#include "scene_level3.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <SFML/Audio.hpp>

// Player shared pointer
static shared_ptr<Entity> player;

//Level audio variables
sf::Music music3;
sf::SoundBuffer buffer3;
sf::Sound endLvl3;

bool isPaused3;

// Load function
//
// Function loads assets for the scene
void Level3Scene::Load() 
{
	// Output message to console when scene is set to load
	cout << "Scene 3 Load" << endl;

	// Load level from level 3 file
	ls::loadCSVLevelFile("res/levels/level3.csv", 40.0f);

	// Have camera target the player start position
	Renderer::setCameraTarget(ls::getTilePosition(ls::findTiles(ls::START)[0]));

	//open the soundtrack file and plays it
	music3.openFromFile("res/audio/music/3_boss.ogg");
	music3.play();

	// Populate the level with entities and wall collision physics
	populateLevel();

	//Simulate long loading times - can be commented out when scene becomes more complex
	//this_thread::sleep_for(chrono::milliseconds(3000));

	// Output message when scene loaded
	cout << " Scene 3 Load Done" << endl;

	// Set loaded to true
	setLoaded(true);
	lvl3 = true;
}

void Level3Scene::UnLoad() 
{
	// Output message to console when scene is unloaded
	cout << "Scene 3 UnLoad" << endl;
	
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
void Level3Scene::Update(const double& dt) 
{
	// Obtain player position
	const auto playerPos = player->getPosition();

	// Set camera to target the player, based on their position
	Renderer::setCameraTarget(playerPos);

	// Check if player has reached end tile
	if (ls::getTileAt(playerPos) == ls::EXIT)
	{
		//end level sound played
		buffer3.loadFromFile("res/audio/fx/level.wav");
		endLvl3.setBuffer(buffer3);
		endLvl3.play();
		music3.stop();
		
		// Change scene to level 1
		Engine::ChangeScene((Scene*)&level1);
	} 
	// Else, check if player is dead
	else if (!player->isAlive()) 
	{
		// Restart level 3
		Engine::ChangeScene((Scene*)&level3);
	}

	// Check if user has pressed the escape key
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		music3.stop();
		// Close the window
		Engine::ChangeScene((Scene*)&menu);
	}

	if (Keyboard::isKeyPressed(Keyboard::Space) || sf::Joystick::isButtonPressed(0, 1))
	{
		if (!isPaused3) {
			isPaused3 = true;
			cout << "PAUSED";
			Engine::PauseScene((Scene*)&pause);
			

		}
		else {
			isPaused3 = false;
		}
	}

	if (!isPaused3) {
		// Update the scene
		Scene::Update(dt);
	}
}

// Render function
//
// Function renders entities in the scene
void Level3Scene::Render() 
{
	// Render tiles
	ls::Render(Engine::GetWindow());

	// Render scene
	Scene::Render();
}
