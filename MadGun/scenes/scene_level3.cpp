/*
 * GAMES ENGINEERING - COURSEWORK
 * -------------------------------------
 * MadGun: Gears and Blood
 * -------------------------------------
 * Franceso Fico - 40404272
 * Graeme White - 40415739
 * -------------------------------------
 * Code Author(s): G. White - F. Fico
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
#include "../components/pause_menu.h"
#include "../components/cmp_text.h"

// Player shared pointer
static shared_ptr<Entity> player;

//Level audio variables
sf::Music music3;
sf::SoundBuffer buffer3;
sf::Sound endLvl3;

// paused bool set to false
bool pausedLvl3 = false;

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

	//if the pause bool is false and space or B are pressed 
	if ((pausedLvl3 == false) && (Keyboard::isKeyPressed(Keyboard::Space)) || (pausedLvl3 == false) && (sf::Joystick::isButtonPressed(0, 1)))
	{
		//if pause is false
		if (pausedLvl3 == false) {
			//bool switch to true
			pausedLvl3 = true;
			//pause background entity created
			_pauseBackground = makeEntity();
			//pause title entity created
			_pauseTitle = makeEntity();
			//pause resume entity created
			_pauseResume = makeEntity();

			//pause component created and set at the player position
			auto pauseBack = _pauseBackground->addComponent<PauseMenu>();
			pauseBack->setPosition(player->getPosition());

			//pause title created and centered in the background
			auto pauseTitle = _pauseTitle->addComponent<TextComponent>("PAUSED");
			float plW = player->getPosition().x;
			float plH = player->getPosition().y;
			pauseTitle->setFont("gotham.ttf");
			pauseTitle->setCharacterSize(150.0f);
			pauseTitle->setLetterSpacing(5.0f);
			pauseTitle->setColour(Color::White);
			pauseTitle->setPosition(Vector2f(plW - 475.f, plH - 200.f));

			//pause resume created and set at the bottom of the page
			auto pauseResume = _pauseResume->addComponent<TextComponent>("press Enter to resume");
			pauseResume->setFont("gotham.ttf");
			pauseResume->setLetterSpacing(5.0f);
			pauseResume->setColour(Color::Red);
			pauseResume->setCharacterSize(50.0f);
			pauseResume->setPosition(Vector2f(plW - 475.f, plH + 350.f));
		}
	}
	//if pause is true and enter or controller X is pressed
	if ((pausedLvl3 == true) && (Keyboard::isKeyPressed(Keyboard::Return)) || (pausedLvl3 == true) && (sf::Joystick::isButtonPressed(0, 0)))
	{
		// pause bool set to true
		pausedLvl3 = false;
		//pause entities are deleted
		_pauseBackground->setForDelete();
		_pauseTitle->setForDelete();
		_pauseResume->setForDelete();

	}

	if (!pausedLvl3) //unpaused update
	{
		// Check if user has pressed the escape key
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			// Close the window
			Engine::ChangeScene((Scene*)&menu);
			music3.stop();
		}

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
