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
 * SYSTEM RENDERER - system_renderer.cpp
 *
 * System renderer
 *
 */

// Libraries
#include "system_renderer.h"
#include <queue>

// Sprite queue
static queue<const Drawable*> sprites;

// Render Window
static RenderWindow* rw;

// Game Width
constexpr uint16_t gameWidth = 1920;

// Game Height
constexpr uint16_t gameHeight = 1080;

// Camera
static View theCamera(FloatRect(0.0f, 0.0f, (float)gameWidth, (float)gameHeight));

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

// Set Camera Target function
//
// Function sets the camera to target a specific vector
// Can be used to 
void Renderer::setCameraTarget(Vector2f vect)
{
	// Set camera's centre
	theCamera.setCenter(vect);
}

// Set Camera Zoom
//
// Function sets the camera's zoom level
void Renderer::setCameraZoom(float zoom)
{
	// Set camera's zoom
	theCamera.zoom(zoom);
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

	// Set camera view 
	rw->setView(theCamera);
}

// Queue function
//
// Function for queueing drawable sprites
void Renderer::queue(const Drawable* s) 
{ 
	// Add sprite to the queue
	sprites.push(s); 
}