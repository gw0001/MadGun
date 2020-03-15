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
 * SYSTEM RENDERER - system_renderer.h
 *
 * Header file for system renderer
 *
 */

// Library
#pragma once
#include <SFML/Graphics.hpp>
//#include "cmp_sprite.h"

// Namespaces
using namespace sf; // SFML namespace
using namespace std; // Standard namespace

/*
 * RENDERER NAMESPACE
 */
namespace Renderer 
{
	// Initialise function
	void initialise(RenderWindow&);

	// Shutdown function
	void shutdown();

	// Update function
	void update(const double&);

	// Queue function
	void queue(const Drawable* s);

	// Render function
	void render();
};
