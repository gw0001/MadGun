/*
 * GAMES ENGINEERING - COURSEWORK
 * -------------------------------------
 * MadGun: Gears and Blood
 * -------------------------------------
 * Franceso Fico - 40404272
 * Graeme White - 40415739
 * -------------------------------------
 * Code Author: G. White
 * Date Created: 14/03/2020
 * Date Last Modified: 22/04/2020
 * -------------------------------------
 * ENGINE - engine.cpp
 *
 * Engine
 *
 */

// Libraries
#include "engine.h"
#include "maths.h"
#include "system_physics.h"
#include "system_renderer.h"
#include "system_resources.h"
#include <SFML/Graphics.hpp>
#include <future>
#include <iostream>
#include <stdexcept>
#include "levelsystem.h"

// Component Libraries
#include "../MadGun/components/cmp_player_physics.h"
#include "../MadGun/components/cmp_sprite.h"
#include "../MadGun/components/cmp_physics.h"
#include "../MadGun/components/cmp_hurt_player.h"
#include "../MadGun/components/cmp_enemy_ai.h"
#include "../MadGun/components/cmp_enemy_turret.h"

// Active scene pointer
Scene* Engine::_activeScene = nullptr;

// Game Name string
string Engine::_gameName;

// Loading boolean
static bool loading = false;

// Loading spinner, set to 0
static float loadingspinner = 0.0f;

// Loading time
static float loadingTime;

float turretFirerate = 3.5f;

// Render Window
static RenderWindow* _window;

// Loading Update function
//
// Function updates the entities of the loading screen
void Loading_update(float dt, const Scene* const scn) 
{
	// Output message to console to when loading screen is active - Will cause FPS to drop when enabled
	//cout << "Eng: Loading Screen\n";

	// Check is scene is loaded
	if (scn->isLoaded()) 
	{
		// Scene loaded, display exiting loading screen message
		cout << "Eng: Exiting Loading Screen\n";

		// Set loading to false
		loading = false;
	}
	// Scene not loaded
	else 
	{
		// Increment loading spinner by 220.0 mulitplied by time slice
		loadingspinner += 220.0f * dt;

		// Increment loading time by time slice
		loadingTime += dt;
	}
}

// Loading Render function
//
// Function renders entites for the loading screen
void Loading_render() 
{
	// Output loading message to console - Will cause FPS to drop when enabled
	//cout << "Eng: Loading Screen Render\n";

	// Create Circle Loading shape
	static CircleShape octagon(80, 8);

	// Set loading circle origin
	octagon.setOrigin(80, 80);

	// Set the camera to target the loading wheel
	Renderer::setCameraTarget(octagon.getPosition());

	// Set rotation
	octagon.setRotation(loadingspinner);

	// Set position
	octagon.setPosition(Vcast<float>(Engine::getWindowSize()) * .5f);

	// Set fill colour (will fade in over time)
	octagon.setFillColor(Color(255, 255, 255, min(255.f, 40.f * loadingTime)));

	// Loading text
	static Text t("Loading", *Resources::get<Font>("arial.ttf"));

	// Set text fill colour
	t.setFillColor(Color(255, 255, 255, min(255.f, 40.f * loadingTime)));

	// Set text position
	t.setPosition(Vcast<float>(Engine::getWindowSize()) * Vector2f(0.4f,0.3f));

	// Add text to the render queue
	Renderer::queue(&t);

	// Add shape to the render queue
	Renderer::queue(&octagon);
}

// Frame times
float frametimes[256] = {};

// Frame Time Counter
uint8_t ftc = 0;


// Update Function
//
// Function updates the engine of the game
void Engine::Update() 
{
	// Clock object
	static Clock clock;

	// Time Increment
	float dt = clock.restart().asSeconds();

	// FRAMES PER SECOND CALCULATION
	{
		// Determine frame times
		frametimes[++ftc] = dt;

		// Average FPS Counter
		static string avg = _gameName + " FPS:";

		// Check modulus of ftc leaves no remainder when divisible by 60 (the desired FPS of the game)
		if (ftc % 60 == 0) 
		{
			// Decimal point average
			double davg = 0;

			// Iterate over all frame times
			for (const auto t : frametimes) 
			{
				// Increment decimal point average by t
				davg += t;
			}

			// Determine decimal point average
			davg = 1.0 / (davg / 255.0);

			// Display Average FPS counter to the window title
			_window->setTitle(avg + toStrDecPt(2, davg));
		}
	}

	// Check if loading
	if (loading) 
	{
		// Loading, carry out update
		Loading_update(dt, _activeScene);
	} 
	// Else, check if active scene exists
	else if (_activeScene != nullptr) 
	{
		// Update the Physics engine by time increment
		Physics::update(dt);

		// Update the active scene
		_activeScene->Update(dt);
	}
}

// Render function
//
// Function renders 
void Engine::Render(RenderWindow& window) 
{
	// Check if loading
	if (loading) 
	{
		// Display loading render
		Loading_render();
	} 
	// Else, check active scene exists
	else if (_activeScene != nullptr) 
	{
		// Render Active Scene
		_activeScene->Render();
	}

	// Render
	Renderer::render();
}

// Start function
//
// Function starts the game
void Engine::Start(unsigned int width, unsigned int height, const string& gameName, Scene* scn) 
{
	// Render Window
	RenderWindow window(VideoMode(width, height), gameName);

	// Set game name
	_gameName = gameName;

	// Set Render Window
	_window = &window;

	// Initialise render window
	Renderer::initialise(window);

	// Initialise Physics
	Physics::initialise();

	// Change Scene
	ChangeScene(scn);

	// Loop whilst the window is open
	while (window.isOpen()) 
	{
		// Event object
		Event event;

		// While event object exists
		while (window.pollEvent(event)) 
		{
			// Check if envent is of type closed
			if (event.type == Event::Closed) 
			{
				// Close the window
				window.close();
			}
		}

		//// Check if user has pressed the escape key
		//if (Keyboard::isKeyPressed(Keyboard::Escape)) 
		//{
		//	// Close the window
		//	window.close();
		//}

		// Clear the render window
		window.clear();

		// Update the game
		Update();

		// Render the game to the window
		Render(window);

		// Display the window
		window.display();
	}

	// Check Active scene exists
	if (_activeScene != nullptr) 
	{
		// Unload active scene
		_activeScene->UnLoad();

		// Set active scene to null pointer
		_activeScene = nullptr;
	}

	// Close Window
	window.close();

	// Shutdown Physics
	Physics::shutdown();

	// Renderer shutdown
	Renderer::shutdown();
}

// Make Entity function
//
// Function for creating an entity
shared_ptr<Entity> Scene::makeEntity() 
{
	// Create shared point entity
	auto e = make_shared<Entity>(this);

	// Add entity to the entity manager list
	ents.list.push_back(e);

	// Return entity
	return move(e);
}

// Create player function
//
// Function to create the player
void Scene::createPlayer()
{
	// Create player entity
	player = makeEntity();

	// Set player to starting position
	player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));

	// Right Facing Player Texture Shared Pointer
	shared_ptr<Texture> playerRightTexture;

	// Left Facing Player Texture Shared Pointer
	shared_ptr<Texture> playerLeftTexture;

	// Load right facing texture
	playerRightTexture = Resources::get<Texture>("player_right.png");

	// Load left facing texture
	playerLeftTexture = Resources::get<Texture>("player_left.png");

	// Texture Width
	int textureWidth = playerRightTexture->getSize().x;

	// Texture Height
	int textureHeight = playerRightTexture->getSize().y;

	// Note - both left and right textures have the same width and height
	// Only need to obtain values for the height and width once

	// Add player sprite component to the player entity
	auto s = player->addComponent<PlayerSpriteComponent>();

	// Set up left facing texture
	s->setLeftFacingTexure(playerLeftTexture);

	// Set up right facing texture
	s->setRightFacingTexure(playerRightTexture);

	// Set player origin
	s->getSprite().setOrigin(Vector2f(textureWidth / 2, textureHeight / 2 + 12));

	// Add Physics component to the player
	player->addComponent<PlayerPhysicsComponent>(Vector2f(20.f, 30.f));

	// Add player tag
	player->addTag("player");
}

// Create Enemy Function
//
// Function to create an enemy, based on the
// value of the enemy type integer argument
void Scene::createEnemy(int enemyType)
{
	// Enemy Tile Set
	ls::Tile enemyTileSet;

	// Enemy Texture Shared Pointer
	shared_ptr<Texture> enemyTexture;

	// Texture Width
	int textureWidth;

	// Texture Height
	int textureHeight;

	// Check if argument number is 1
	if (enemyType == 1)
	{
		// Set tile set to ENEMY_1
		enemyTileSet = ls::ENEMY_1;

		// Set enemy Texture to Enemy 1
		enemyTexture = Resources::get<Texture>("enemy_1.png");
	}
	// Else, check if argument number is 2
	else if (enemyType == 2)
	{
		// Set tile set to ENEMY_2
		enemyTileSet = ls::ENEMY_2;

		// Set enemy Texture to Enemy 2
		enemyTexture = Resources::get<Texture>("enemy_2.png");
	}
	// Else, check if argument number is 3
	else if (enemyType == 3)
	{
		// Set tile set to ENEMY_3
		enemyTileSet = ls::ENEMY_3;

		// Set enemy Texture to Enemy 3
		enemyTexture = Resources::get<Texture>("enemy_3.png");
	}
	// Else, check if argument number is 4
	else if (enemyType == 4)
	{
		// Set tile set to ENEMY_4
		enemyTileSet = ls::ENEMY_4;

		// Set enemy Texture to Enemy 4
		enemyTexture = Resources::get<Texture>("enemy_4.png");
	}
	// Else, check if argument number is 5
	else if (enemyType == 5)
	{
		// Set tile set to ENEMY_5
		enemyTileSet = ls::ENEMY_5;

		// Set enemy Texture to Enemy 5
		enemyTexture = Resources::get<Texture>("enemy_5.png");
	}

	// Find enemy tiles from level
	auto enemyTiles = ls::findTiles(enemyTileSet);

	// Obtain Texture Width
	textureWidth = enemyTexture->getSize().x;

	// Obtain Texture Height
	textureHeight = enemyTexture->getSize().y;

	// Check that relevant tiles have been found within the level
	if (enemyTiles.size() > 0)
	{
		// Relevant tile exists
		for (auto enemyTile : enemyTiles)
		{
			// Make enemy entity
			auto enemy = makeEntity();

			// Obtain enemy tile position and offset
			Vector2f enemyTilePos = ls::getTilePosition(enemyTile) + Vector2f(ls::getTileSize() / 2.0f, ls::getTileSize() - textureHeight / 2);

			// Set enemy position to an enemy tile
			enemy->setPosition(enemyTilePos);

			// Add an enemy AI Component to the entity
			auto enemyAI = enemy->addComponent<EnemyAIComponent>();

			// Check if enemy type is 1
			if (enemyType == 1)
			{
				// Set enemy to fast speed
				enemyAI->setSpeed(125.0f);
			}
			else if (enemyType == 2)
			{
				// Set enemy to normal speed
				enemyAI->setSpeed(100.0f);
			}
			else if (enemyType == 3)
			{
				// Set enemy to normal speed
				enemyAI->setSpeed(100.0f);
			}
			else if (enemyType == 4)
			{
				// Set enemy to slow speed
				enemyAI->setSpeed(75.0f);
			}
			else if (enemyType == 5)
			{
				// Set enemy to very slow speed
				enemyAI->setSpeed(50.0f);
			}

			// Allow entity to hurt the player
			enemy->addComponent<HurtComponent>();

			// Add shape component to the enemy entity
			auto s = enemy->addComponent<SpriteComponent>();

			// Apply Enemy Texture
			s->setTexure(enemyTexture);

			// Set enemy origin
			s->getSprite().setOrigin(Vector2f(textureWidth/2, textureHeight/2));
		}
	}
}

// Create Hazard function
//
// Function for creating hazard entities found within the level
void Scene::createHazards(int hazardType)
{
	// Hazard Tile Set
	ls::Tile hazardTileSet;

	// Hazard Texture Shared Pointer
	shared_ptr<Texture> hazardTexture;

	// Texture Width
	int textureWidth;

	// Texture Height
	int textureHeight;

	// Check if argument number is 1
	if (hazardType == 1)
	{
		// Set tile set to HAZARD_1
		hazardTileSet = ls::HAZARD_1;

		// Set Hazard Texture to Spikes Facing Up
		hazardTexture = Resources::get<Texture>("spikeFacingUp.png");
	}

	// Else, check if argument number is 2
	else if (hazardType == 2)
	{
		// Set tile set to HAZARD_2
		hazardTileSet = ls::HAZARD_2;

		// Set hazard Texture to Spikes Facing Down
		hazardTexture = Resources::get<Texture>("spikeFacingDown.png");
	}
	// Else, check if argument number is 3
	else if (hazardType == 3)
	{
		// Set tile set to HAZARD_3
		hazardTileSet = ls::HAZARD_3;

		// Set hazard Texture to Turret
		hazardTexture = Resources::get<Texture>("turret3.png");
	}

	// Find hazard tiles from level
	auto hazardTiles = ls::findTiles(hazardTileSet);

	// Obtain Texture Width
	textureWidth = hazardTexture->getSize().x;

	// Obtain Texture Height
	textureHeight = hazardTexture->getSize().y;

	// Check that relevant tiles have been found within the level
	if (hazardTiles.size() > 0)
	{
		// Relevant hazard exists
		for (auto hazardTile : hazardTiles)
		{
			// Make hazard entity
			auto hazard = makeEntity();

			// Hazard Position
			Vector2f hazardTilePos;

			// If hazard type is considered a turret
			if (hazardType == 3)
			{
				// Obtain hazard tile position and offset
				hazardTilePos = ls::getTilePosition(hazardTile) + Vector2f(ls::getTileSize() / 2.0f, 0.0f);

			}
			// Else, other hazard
			else
			{
				// Obtain hazard tile position and offset
				hazardTilePos = ls::getTilePosition(hazardTile) + Vector2f(ls::getTileSize() / 2.0f, ls::getTileSize() - textureHeight / 2);

			}

			// Set hazard position to a hazard tile
			hazard->setPosition(hazardTilePos);

			// Add shape component to the hazard entity
			auto s = hazard->addComponent<SpriteComponent>();

			// Apply hazard Texture
			s->setTexure(hazardTexture);

			// Scale the hazard sprite
			s->getSprite().setScale(Vector2f(ls::getTileSize() / textureWidth, ls::getTileSize() / textureHeight));

			// Set hazard origin
			s->getSprite().setOrigin(Vector2f(textureWidth / 2, ls::getTileSize() / 2 - 1));

			// If hazard type is considered a turret
			if (hazardType == 3)
			{
				// Make hazard into a roof turret
				auto turret = hazard->addComponent<EnemyTurretComponent>();

				// Set fire rate
				turret->setFireTime(turretFirerate);
			}
			// Else, other hazards
			else
			{
				// Allow entity to hurt the player
				hazard->addComponent<HurtComponent>();
			}
		}
	}
}

// Add Wall Physics
//
// Function to add wall physics to relevante tiles
// found in the level
void Scene::addWallPhysics()
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

// Populate Level function
//
// Function populates the level with all the revelant 
// entities after a tiled level has been created.
// Function invokes other functions to spawn player,
// enemies and hazards
void Scene::populateLevel()
{
	// Invoke create player entity
	createPlayer();

	// Add wall physics colliders
	addWallPhysics();

	// Iterate over all enemy types
	for (int i = 1; i < numberOfEnemyTypes + 1; i++)
	{
		// Invoke create enemy function
		createEnemy(i);
	}

	// Create Hazards
	for (int i = 1; i < numberOfHazardTypes + 1; i++)
	{
		// Invoke create hazards function
		createHazards(i);
	}
}


// Set Vsync function
//
// Function for enabling or disabling Vertical Sync
void Engine::setVsync(bool b)
{ 
	// Set the vertical sync
	_window->setVerticalSyncEnabled(b); 
}

// Quit function
//
// Function closes the game window and quits the game
void Engine::quitGame()
{
	_window->close();
}

// Change Scene function
//
// Function for changing the scene
void Engine::ChangeScene(Scene* s) 
{
	// Display message to console when changing the scene
	cout << "Eng: changing scene: " << s << endl;

	// Take active scene as the old scene
	auto old = _activeScene;

	// Set active scene to the new scene
	_activeScene = s;

	// Check if old scene still exists
	if (old != nullptr) 
	{
		// Unload old scene
		old->UnLoad();
	}

	// Check if new scene hasn't loaded
	if (!s->isLoaded()) 
	{
		// Display message 
		cout << "Eng: Entering Loading Screen\n";

		// Set loading time to 0
		loadingTime = 0.0f;

		// Load Scene with loading screen - comment out if bypassing the loading screen
		_activeScene->LoadAsync();

		// Load scene without loading screen - will cause game to hang before loading 
		// the next scene. Comment out if using the method that loads the scene with
		// a loading screen
		//_activeScene->Load();

		// Set loading to true
		loading = true;
	}
}

// Update function
//
// Function updates entities in the scene
void Scene::Update(const double& dt) 
{ 
	// Update entities
	ents.update(dt); 
}

// Render function
//
// Function renders entities to window
void Scene::Render() 
{ 
	// Render entities
	ents.render();
}

// Is Loaded Function
//
// Function determines if a scene has loaded or not
bool Scene::isLoaded() const 
{
	{
		// Lock
		lock_guard<mutex> lck(_loaded_mtx);
		
		// Check if loading asynchronously and if it has finished
		if (_loaded_future.valid() && _loaded_future.wait_for(chrono::seconds(0)) ==future_status::ready) 
		{
			// Loading finished
			_loaded_future.get();

			// Set loaded to true
			_loaded = true;
		}

		// Return loaded
		return _loaded;
	}
}

// Set Loaded function
//
// Function sets the status of loaded
void Scene::setLoaded(bool b) 
{
	{
		// Lock
		lock_guard<mutex> lck(_loaded_mtx);

		// Set loaded to value
		_loaded = b;
	}
}

// Unload function
// 
// Function unloads entities from a scene
void Scene::UnLoad() 
{
	// Clear list of entity manager
	ents.list.clear();

	// Set loaded to false
	setLoaded(false);
}

// Load Asynch
//
// Function allows for asynchronously loading 
void Scene::LoadAsync() 
{ 
	// Set loaded future
	_loaded_future = async(&Scene::Load, this); 
}

// Get Window Size
//
// Function returns the size of the window
Vector2u Engine::getWindowSize() 
{ 
	// Return the size of the window
	return _window->getSize(); 
}

// Get Window
//
// Function returns the render window
RenderWindow& Engine::GetWindow() 
{ 
	return *_window; 
}

/*
 * TIMING NAMESPACE
 */
namespace timing 
{
	// Return time since Epoch
	long long now() 
	{
		return chrono::high_resolution_clock::now().time_since_epoch().count();
	}
	// Return time since last() was last called.
	long long last() 
	{
		// Obtain time now
		auto n = now();

		// Obtain time then
		static auto then = now();

		// Determine difference in time
		auto dt = n - then;

		// Set then to n
		then = n;

		// Return time difference
		return dt;
	}
}

// Scene Deconstructor
Scene::~Scene() 
{ 
	// Unload scene
	UnLoad(); 
}