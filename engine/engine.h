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
 * Date Last Modified: 15/03/2020
 * -------------------------------------
 * ENGINE - engine.h
 *
 * Header file for engine
 *
 */

// Libraries
#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <ecm.h>
#include <future>
#include <maths.h>
#include <mutex>
#include <string>

// Namespaces
using namespace sf; // SFML namespace
using namespace std; // Standard namespace

/*
 * SCENE CLASS
 */
class Scene 
{
	public:
		// Scene constructor
		Scene() = default;

		// Scene deconstructor
		virtual ~Scene();

		// Load function
		virtual void Load() = 0;

		// Load Async function
		virtual void LoadAsync();

		// Unload function
		virtual void UnLoad();

		// Update function
		virtual void Update(const double& dt);

		// Render function
		virtual void Render();

		// Is Loaded Function
		bool isLoaded() const;

		// Make Entity function
		shared_ptr<Entity> makeEntity();

		// Entity Manager
		EntityManager ents;

	protected:
		// Set Loaded function
		void setLoaded(bool);

	private:
		// Loaded boolean
		mutable bool _loaded;

		// Loaded Future
		mutable future<void> _loaded_future;

		// Loaded Mutex
		mutable mutex _loaded_mtx;
};

/*
 * ENGINE CLASS
 */
class Engine 
{
	public:
		// Engine constructor
		Engine() = delete;

		// Start function
		static void Start(unsigned int width, unsigned int height, const string& gameName, Scene* scn);

		// Change Scene function
		static void ChangeScene(Scene*);

		// Get Window function
		static RenderWindow& GetWindow();

		// Get Window Size function
		static Vector2u getWindowSize();

		// Set Vsync function
		static void setVsync(bool b);

	private:
		// Active Scene
		static Scene* _activeScene;

		// Game Name
		static string _gameName;

		// Update function
		static void Update();

		// Render Function
		static void Render(RenderWindow& window);
};

/*
 * TIMING NAMESPACE
 */
namespace timing 
{
	// Return time since Epoch
	long long now();

	// Return time since last() was last called.
	long long last();
}