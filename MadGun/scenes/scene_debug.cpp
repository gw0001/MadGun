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
 * Date Last Modified: 18/04/2020
 * -------------------------------------
 * DEBUG SCENE - scene_debug.cpp
 *
 * Debug Level, for testing various
 * aspects of the game
 *
 */

// Libraries
#include "scene_debug.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_sprite.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>

// Player Shared Pointer
static shared_ptr<Entity> player;

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

	// Create player
	{
		// Create player entity
		player = makeEntity();

		// Set player to starting position
		player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));

		// Add shape component to the player
		auto s = player->addComponent<ShapeComponent>();

		// Set shape component of the player
		s->setShape<RectangleShape>(Vector2f(20.f, 30.f));

		// Set fill colour of the player
		s->getShape().setFillColor(Color::Magenta);

		// Set player's origin
		s->getShape().setOrigin(10.f, 15.f);

		// Add Physics component to the player
		player->addComponent<PlayerPhysicsComponent>(Vector2f(20.f, 30.f));
	}

	// Add physics colliders to level tiles.
	{
		// Find all wall tiles in the level
		auto walls = ls::findWallTiles();
		
		// Iterate over each wall tile
		for (auto w : walls) 
		{
			// Obtain wall tile position
			auto pos = ls::getTilePosition(w);

			// Offset the position to the centre
			pos += Vector2f(ls::getTileSize() / 2.0f, ls::getTileSize() / 2.0f);

			// Make entity
			auto e = makeEntity();

			// Set position of the entity
			e->setPosition(pos);

			// Add Physics component to the entity
			e->addComponent<PhysicsComponent>(false, Vector2f(ls::getTileSize(), ls::getTileSize()));
		}
	}

	//Simulate long loading times - can be commented out when scene becomes more complex
	this_thread::sleep_for(chrono::milliseconds(3000));

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

	// Check if R key pressed
	if (Keyboard::isKeyPressed(Keyboard::R))
	{
		Reset();
	}

	// Check if user has pressed the escape key
	if (Keyboard::isKeyPressed(Keyboard::Escape))
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
