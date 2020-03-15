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
 * SYSTEM RESOURCES - system_resources.h
 *
 * Header file for system resources
 *
 */

// Libraries
#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <memory>
#include <string>
// SOUND
#ifdef SOUND
#include <SFML/Audio/Sound.hpp>
#endif 

// Namespaces
using namespace std; // Standard Namespace
using namespace sf; // SFML Namespace

/*
 * RESOURCES NAMESPACE
 */
namespace Resources 
{
	// Load function (Template)
	template <typename T> shared_ptr<T> load(const string& name) 
	{
		// Throw error message as it is unavailable to load this type
		throw("Resource loader unavailable for this type");
	}

	// Load function - Font (Template)
	template <> // explicit specialization for T = Font
	shared_ptr<Font> load(const string& name);

	// Load function - Texture (Template)
	template <> // explicit specialization for T = texture
	shared_ptr<Texture> load(const string& name);

	#ifdef SOUND
	// Load function - Sound Buffer (Template)
	template <> // explicit specialization for T = SoundBuffer
	shared_ptr<SoundBuffer> load(const string& name);

	// Load function - Music (Template)
	template <> // explicit specialization for T = Music
	shared_ptr<Music> load(const string& name);
	#endif // SOUND

	// Get Function (Template)
	template <typename T>
	static shared_ptr<T> get(const string& name) 
	{
		// Map of items
		static map<string, shared_ptr<T>> _things;

		// Obtain items matching specified name
		auto search = _things.find(name);

		// Check search has not reached the end of the map
		if (search != _things.end()) 
		{
			// Add item to the things map
			return search->second;
		} 
		else 
		{
			// Load item from things map
			_things[name] = load<T>(name);

			// Return the item(s)
			return _things[name];
		}
	};
}