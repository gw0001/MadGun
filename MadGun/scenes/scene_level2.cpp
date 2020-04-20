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
 * LEVEL 2 SCENE - scene_level2.cpp
 *
 * Level 2 of MadGun.
 *
 */

// Libraries
#include "scene_level2.h"
#include "../components/cmp_enemy_ai.h"
#include "../components/cmp_enemy_turret.h"
#include "../components/cmp_hurt_player.h"
#include "../components/cmp_physics.h"
#include "../components/cmp_player_physics.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <SFML/Audio.hpp>

// Player shared pointer
static shared_ptr<Entity> player;

//Level audio variables
sf::Music music2;
sf::SoundBuffer buffer2;
sf::Sound endLvl2;

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

	// Create player
	{
		//open the soundtrack file and plays it
		music2.openFromFile("res/audio/music/2_landing.ogg");
		music2.play();

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

		// Add player tag
		player->addTag("player");

		// Add physics component to player
		player->addComponent<PlayerPhysicsComponent>(Vector2f(20.f, 30.f));
	}

	// Create Enemy
	{
		// Make enemy entity
		auto enemy = makeEntity();

		// Set enemy position to enemy tile and add vertical offset
		enemy->setPosition(ls::getTilePosition(ls::findTiles(ls::HAZARD_1)[0]) + Vector2f(0, 24));

		// Add HurtComponent to the enemy
		enemy->addComponent<HurtComponent>();

		// Add shape component to the enemy
		auto s = enemy->addComponent<ShapeComponent>();

		// Set shape component of the enemy
		s->setShape<CircleShape>(16.0f);

		// Set fill colour of the player
		s->getShape().setFillColor(Color::Red);

		// Set player's origin
		s->getShape().setOrigin(16.0f, 16.0f);

		// Add EnemyAIComponent
		enemy->addComponent<EnemyAIComponent>();
	}

	//// Create Turret
	//{
	//	// Create turret entity
	//	auto turret = makeEntity();

	//	// Set enemy position to turret tile (character t) and add horizontal offset
	//	turret->setPosition(ls::getTilePosition(ls::findTiles('t')[0]) + Vector2f(ls::getTileSize() / 2.0f, 0));
	//	
	//	// Add shape component to turret
	//	auto s = turret->addComponent<ShapeComponent>();
	//	
	//	// Set to circle shape, size 16, with 3 points (will make a triangle)
	//	s->setShape<sf::CircleShape>(16.0f, 3);

	//	// Set turret to red
	//	s->getShape().setFillColor(Color::Red);

	//	// Set origin of the turret
	//	s->getShape().setOrigin(16.f, 16.f);

	//	// Add Enemy Turret Component
	//	turret->addComponent<EnemyTurretComponent>();
	//}

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

	// Check if user has pressed the escape key
	if (Keyboard::isKeyPressed(Keyboard::Escape) || sf::Joystick::isButtonPressed(0, 1))
	{
		music2.stop();
		// Close the window
		Engine::ChangeScene((Scene*)&menu);
	}

	// Update the scene
	Scene::Update(dt);
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
