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
 * SYSTEM RESOURCES 
 * - system_resources.cpp
 *
 * System resources
 *
 */

// Libraries
#include "system_resources.h"

/*
 * RESOURCES NAMESPACE
 */
namespace Resources 
{
	// Load function - Font (Template)
	template<>
	shared_ptr<Font> load(const string &name) 
	{
		// Font shared pointer
		auto f = make_shared<Font>();

		// Check desired font exists in resource directory
		if (!f->loadFromFile("res/fonts/" + name)) 
		{
			// Font not found, throw error message to console
			throw("not found: " + name);
		};

		// Return font
		return f;
	};

	// Load function - Texture (Template)
	template <>
	shared_ptr<Texture> load(const string& name) 
	{
		// Texture shared pointer
		auto tex = make_shared<Texture>();

		// Check desired texture exists in resource folder
		if (!tex->loadFromFile("res/img/" + name)) 
		{
			// Texture not found, throw error message to console
			throw("not found: " + name);
		};

		// Return texture
		return tex;
	};

	// SOUND
	#ifdef SOUND
	// Find function - Sound Buffer (template)
	template <> // explicit specialization for T = SoundBuffer
	shared_ptr<SoundBuffer> load(const string& name) 
	{
		// Sound Buffer shared pointer
		auto buf = make_shared<SoundBuffer>();

		// Check sound file exists in resource folder
		if (!buf->loadFromFile("res/sound/" + name)) 
		{
			// Sound not found, throw error message to console
			throw("not found: " + name);
		};

		// Return sound buffer
		return buf;
	};

	// Find function - Music (template)
	template <> // explicit specialization for T = Music
	shared_ptr<Music> load(const string& name) 
	{
		// Music shared pointer
		auto music = make_shared<Music>();

		// Check if music file exists in resource folder
		if (!music->openFromFile("res/sound/" + name)) 
		{
			// Music not found, throw error message to console		
			throw("not found: " + name);
		};

		// Return music file
		return music;
	};
	#endif
}