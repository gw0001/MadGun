/*
 * GAMES ENGINEERING - COURSEWORK
 * -------------------------------------
 * MadGun: Gears and Blood
 * -------------------------------------
 * Franceso Fico - 
 * Graeme White - 40415739
 * -------------------------------------
 * Code Author: G. White
 * Date Created: 02/03/2020
 * Date Last Modified: 02/03/2020
 * -------------------------------------
 * main.cpp
 *
 * Main file for the MadGun game.
 *
 * Currently populated with boilerplate SFML code
 */

 // Libraries
#include <SFML/Graphics.hpp>

// Namespaces
using namespace sf; // SFML namespace
using namespace std; // STD namespace

// Game Width
int gameWidth = 1920;
// Game Height
int gameHeight = 1080;

// Reset Function
//
// Function resets game world to initial state
void Reset()
{
	// Code for initial state(s)
}

// Load Function
//
// Function loads assets into game world
void Load()
{
	// Code for loading assets into game world

	// Calling Reset function to set assets to initial state (if needed)
	Reset();
}

// Update Function
//
// Function updates entities
void Update(RenderWindow &aWindow)
{
	// Reset the clock and recalculate the deltaTime
	static Clock clock; // Clock object
	float dt = clock.restart().asSeconds(); // Delta time - time increment

	// Event object
	Event event;

	// Check and consume events
	while (aWindow.pollEvent(event))
	{
		// Check if event is closed
		if (event.type == Event::Closed)
		{
			// Close the window
			aWindow.close();
			return;
		}
	}

	// Escape key - quit the game
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		// Close the window
		aWindow.close();
	}


	// Additional code can go here for updating entities

}

// Render Function
//
// Function renders entities to render window
void Render(RenderWindow &aWindow)
{
	// Code for rendering entities to window/game world
}

// Main function
//
// Function is called when program is booted
int main()
{
	// Determine the width, height, and text for the window
	RenderWindow window(VideoMode(gameWidth, gameHeight), "MadGun: Gears and Blood");

	float circleRadius = 150.0f;

	// Create a circle object with a radius of 100.0f
	sf::CircleShape shape(circleRadius);

	// Set origin of circle
	shape.setOrigin(circleRadius, circleRadius);

	// Set circle to green colour
	shape.setFillColor(sf::Color::Green);

	// Set position of the green circle
	shape.setPosition(gameWidth / 2.0f, gameHeight / 2.0f);

	// Loop whilst the window is open
	while (window.isOpen())
	{
		// Event object
		Event event;

		// Loop whilst event doesn't meet certain condition
		while (window.pollEvent(event))
		{
			// Check to determine if the event is "closed"
			if (event.type == sf::Event::Closed)
			{
				// Close window when event is "closed"
				window.close();
			}
		}

		// Clear the window
		window.clear();

		// Draw the circle in the window
		window.draw(shape);

		// Display the window 
		window.display();
	}
	return 0;
}