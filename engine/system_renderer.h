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
 * Date Last Modified: 16/04/2020
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

	// Set Camera Centre
	void setCameraTarget(Vector2f vect);

	// Set Camera Zoom
	void setCameraZoom(float zoom);

	// Render function
	void render();
};
