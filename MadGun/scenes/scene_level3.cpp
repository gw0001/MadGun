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
 * LEVEL 3 SCENE - scene_level3.cpp
 *
 * Level 3 of MadGun.
 *
 * Currently populated with boilerplate
 * platformer code from practicals
 */

// Library
#include "scene_level3.h"
#include "../components/cmp_physics.h"
#include "../components/cmp_player_physics.h"
#include "../game.h"
#include "../components/cmp_bullet.h"
#include <LevelSystem.h>
#include <iostream>
#include <SFML/Audio.hpp>

// Player shared pointer
static shared_ptr<Entity> player;

//Level soundtrack
sf::Music music3;

// Load function
//
// Function loads assets for the scene
void Level3Scene::Load() 
{
	// Output message to console when scene is set to load
	cout << "Scene 3 Load" << endl;

	// Load level from level 3 file
	//ls::loadTXTLevelFile("res/levels/level_3.txt", 40.0f);

	// Load level from level 3 file
	ls::loadCSVLevelFile("res/levels/labLevel3.csv", 40.0f);

	// Determine height offset
	//auto ho = Engine::getWindowSize().y - (ls::getHeight() * ls::getTileSize());
	
	// Set tile offset
	//ls::setOffset(Vector2f(0, ho));

	// Create player
	{
		//open the soundtrack file and plays it
		music3.openFromFile("res/audio/music/3_boss.ogg");
		music3.play();

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

	// Add physics colliders to level tiles.
	{
		// Find all wall tiles in the level
		auto walls = ls::findTiles(ls::WALL);

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
	if (ls::getTileAt(playerPos) == ls::END)
	{
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

	//// Rock time
	//static float rocktime = 0.0f;

	//// Decrement rock time by time slice
	//rocktime -= dt;

	//// Check if rock time is less than, or equal to, 0
	//if (rocktime <= 0.f)
	//{
	//	// Set rock time to 5.0f
	//	rocktime  = 5.f;

	//	// Make Rock entity
	//	auto rock = makeEntity();

	//	// Spawn rock at rock tile (r) and add vertical offset
	//	rock->setPosition(ls::getTilePosition(ls::findTiles('r')[0]) + Vector2f(0, 40) );

	//	// Add bullet component to the rock, with a life of 30 seconds
	//	rock->addComponent<BulletComponent>(30.f);

	//	// Add shape component to the rock
	//	auto s = rock->addComponent<ShapeComponent>();

	//	// Set shape component of the rock to a circle of size 40
	//	s->setShape<CircleShape>(40.f);

	//	// Set rock colour to cyan
	//	s->getShape().setFillColor(Color::Cyan);

	//	// Set origin of the rock
	//	s->getShape().setOrigin(40.f, 40.f);

	//	// Add physics component to the rock
	//	auto p = rock->addComponent<PhysicsComponent>(true, Vector2f(75.f, 75.f));
	//	
	//	// Set Restitution of rock
	//	p->setRestitution(.4f);

	//	// Set rock's friction value
	//	p->setFriction(.0001f);

	//	// Apply impulse of -3 in x (will cause rock to move from right to left)
	//	p->impulse(Vector2f(-3.0f, 0));

	//	// Set mass of rock
	//	p->setMass(1000000000.0f);
	//}
  
	Renderer::setCameraZoom(gameZoom);

	// Update scene
	Scene::Update(dt);
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
