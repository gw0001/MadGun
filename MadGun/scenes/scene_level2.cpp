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
 * LEVEL 2 SCENE - scene_level2.cpp
 *
 * Level 2 of MadGun.
 *
 */

// Libraries
#include "scene_level2.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include "../components/pause_menu.h"
#include "../components/cmp_text.h"
#include <SFML/Audio.hpp>

// Player shared pointer
static shared_ptr<Entity> player;

//Level audio variables
sf::Music music2;
sf::SoundBuffer buffer2;
sf::Sound endLvl2;

// paused bool set to false
bool pausedLvl2 = false;

// Load function
//
// Function loads entities into the scene
void Level2Scene::Load() 
{
	// Output message to console when scene is changing to level 2
	cout << "Scene 2 Load" << endl;

	// Load Level from level file
	ls::loadCSVLevelFile("res/levels/level2.csv", 40.0f);

	// Have camera target the player start position
	Renderer::setCameraTarget(ls::getTilePosition(ls::findTiles(ls::START)[0]));

	//open the soundtrack file and plays it
	music2.openFromFile("res/audio/music/2_landing.ogg");
	music2.play();

	// Populate Level
	populateLevel();

	//Simulate long loading times - can be commented out when scene becomes more complex
	//this_thread::sleep_for(chrono::milliseconds(3000));

	// Output message to console once scene 2 has loaded
	cout << " Scene 2 Load Done" << endl;

	// Set loaded to true
	setLoaded(true);
}

// Unload function
//
// Function unloads the level
void Level2Scene::UnLoad() 
{
	// Output message to console when second scene has been set to unload
	cout << "Scene 2 UnLoad" << endl;

	// Reset the player
	player.reset();

	// Unload the tiles
	ls::unload();

	// Unload the scene
	Scene::UnLoad();
}

// Update function
//
// Function updates the level
void Level2Scene::Update(const double& dt) 
{
	// Obtain player position
	const auto playerPos = player->getPosition();

	// Set camera to target the player, based on their position
	Renderer::setCameraTarget(playerPos);

	// Check if player is at an end tile
	if (ls::getTileAt(playerPos) == ls::EXIT)
	{
		//end level sound played
		buffer2.loadFromFile("res/audio/fx/level.wav");
		endLvl2.setBuffer(buffer2);
		endLvl2.play();
		music2.stop();

		// Change scene to level 3
		Engine::ChangeScene((Scene*)&level3);
	} 
	// Else, check if player has died
	else if (!player->isAlive()) 
	{
		// Reload level 2
		Engine::ChangeScene((Scene*)&level2);
	}

	//if the pause bool is false and space or B are pressed 
	if ((pausedLvl2 == false) && (Keyboard::isKeyPressed(Keyboard::Space)) || (pausedLvl2 == false) && (sf::Joystick::isButtonPressed(0, 1)))
	{
		//if pause is false
		if (pausedLvl2 == false) {
			//bool switch to true
			pausedLvl2 = true;
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
			pauseTitle->setPosition(Vector2f(plW - 475.f, plH / 2.f));

			//pause resume created and set at the bottom of the page
			auto pauseResume = _pauseResume->addComponent<TextComponent>("press Enter to resume");
			pauseResume->setFont("gotham.ttf");
			pauseResume->setLetterSpacing(5.0f);
			pauseResume->setColour(Color::Red);
			pauseResume->setCharacterSize(50.0f);
			pauseResume->setPosition(Vector2f(plW - 475.f, plH + 400.f));
		}
	}
	//if pause is true and enter or controller X is pressed
	if ((pausedLvl2 == true) && (Keyboard::isKeyPressed(Keyboard::Return)) || (pausedLvl2 == true) && (sf::Joystick::isButtonPressed(0, 0)))
	{
		// pause bool set to true
		pausedLvl2 = false;
		//pause entities are deleted
		_pauseBackground->setForDelete();
		_pauseTitle->setForDelete();
		_pauseResume->setForDelete();

	}

	if (!pausedLvl2) //unpaused update
	{
		// Check if user has pressed the escape key
		if (Keyboard::isKeyPressed(Keyboard::Escape) || (sf::Joystick::isButtonPressed(0, 7)))
		{
			// Close the window
			Engine::ChangeScene((Scene*)&menu);
			music2.stop();
		}

		// Update the scene
		Scene::Update(dt);
	}
}

// Render function
//
// Function renders 
void Level2Scene::Render() 
{
	// Render tiles
	ls::Render(Engine::GetWindow());

	// Render scene
	Scene::Render();
}
