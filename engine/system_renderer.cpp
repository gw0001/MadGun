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
 * SYSTEM RENDERER - system_renderer.cpp
 *
 * System renderer
 *
 */

// Library
#include "system_renderer.h"
#include <queue>

// Sprite queue
static queue<const Drawable*> sprites;

// Render Window
static RenderWindow* rw;

// Initialise function
//
// Function initialises the renderer
void Renderer::initialise(RenderWindow& r) 
{ 
	// Set render window
	rw = &r; 
}

// Shutdown function
//
// Function shuts down the renderer
void Renderer::shutdown() 
{
	// Loop whilst sprites queue contains entities to draw
	while (!sprites.empty())
	{
		// Pop sprite at front of the queue
		sprites.pop();
	}
}

// Update function
//
// Function for updating renderer
void Renderer::update(const double&) 
{
}

// Render function
//
// Function for rendering sprites to the render window
void Renderer::render() 
{
	// Check if Render Window exists
	if (rw == nullptr) 
	{
		// No render window exists, throw error message
		throw("No render window set! ");
	}

	// Loop whilst sprites queue contains entities to draw
	while (!sprites.empty()) 
	{
		// Draw sprite at the front of the queue
		rw->draw(*sprites.front());

		// Pop sprite at the front of the queue
		sprites.pop();
	}
}

// Queue function
//
// Function for queueing drawable sprites
void Renderer::queue(const Drawable* s) 
{ 
	// Add sprite to the queue
	sprites.push(s); 
}