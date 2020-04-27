/*
 * GAMES ENGINEERING - COURSEWORK
 * -------------------------------------
 * MadGun: Gears and Blood
 * -------------------------------------
 * Franceso Fico - 40404272
 * Graeme White - 40415739
 * -------------------------------------
 * Code Author(s): G. White
 * Date Created: 23/04/2020
 * Date Last Modified: 23/04/2020
 * -------------------------------------
 * CONTINUE SCENE - scene_continue.cpp
 *
 * Continue Scene for MadGun
 */

// Libraries
#include "scene_continue.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Window/Joystick.hpp>

// Component libraries
#include "../components/cmp_text.h"

// Level Selection Number
int levelSelectionNumber;

// Menu selection change boolean
bool levelMenuSelectionChanged = false;

// Default cooldown time for changing menu selection
float defaultLevelMenuCooldownTime = 0.2f;

// Menu Cool Down time
float levelMenuCooldownTime;

// Can Make Choice
bool canMakeChoice;

// Load Function
//
// Function loads required entities for the continue scene
void ContinueScene::Load() 
{
	// Message to console
	cout << "Menu Load \n";

	// Set Camera position to the middle of the window screen
	Renderer::setCameraTarget(Vector2f(gameWidth / 2, gameHeight / 2));

	// Inistialise Menu selection number
	levelSelectionNumber = 0;

	// Initialise menu cooldown time
	levelMenuCooldownTime = 0.0f;


	// Can make choice boolean
	canMakeChoice = false;

	// Title
	{
		// Create title entity
		_levelSelectTitle = makeEntity();

		// Add Text Component
		auto titleText = _levelSelectTitle->addComponent<TextComponent>("Level Select");

		// Set font to Gotham
		titleText->setFont("gotham.ttf");

		// Set character size to 150.0f
		titleText->setCharacterSize(150.0f);

		// Set letter spacing to 5.0f
		titleText->setLetterSpacing(5.0f);

		// Set text colour to white
		titleText->setColour(Color::White);

		// Set title position
		titleText->setPosition(Vector2f(30.0f, 0.0f));
	}

	// Menu Items
	{
		// Create entities in menu array
		{
			// Iterate over all elements of menu entity array
			for (int i = 0; i < 5; i++)
			{
				// Make menu item entity
				_levelMenu[i] = makeEntity();
			}
		}

		// Apply text and properties to each menu item
		for (int i = 0; i < 5; i++)
		{
			// Add text component with blank string to menu item at position i
			auto menuItem = _levelMenu[i]->addComponent<TextComponent>();

			// If i is 0
			if (i == 0)
			{
				// Change text to "New Game"
				menuItem->setText("Level 1");
			}
			// If i is 1
			else if (i == 1)
			{
				// Change text to "Level Select"
				menuItem->setText("Level 2");
			}
			// If i is 2
			else if (i == 2)
			{
				// Change text to "How to Play"
				menuItem->setText("Level 3");
			}
			// If i is 3
			else if (i == 3)
			{
				// Change text to "Credits"
				menuItem->setText("Level 4");
			}
			// If i is 4
			else if (i == 4)
			{
				// Change text to "Quit Game"
				menuItem->setText("Level 5");
			}

			// Set font to Gotham
			menuItem->setFont("gotham.ttf");

			// Set character size to 75.0f
			menuItem->setCharacterSize(75.0f);

			// Set text colour to grey
			menuItem->setColour(Color(110, 110, 110));

			// Set position of each menu item depending on the value of i
			menuItem->setPosition(Vector2f(150.0f, 250.0f + (i * 120.0f)));
		}
	}
}

// Update Function
//
// Function updates the continue scene
void ContinueScene::Update(const double& dt) 
{

	// Highlight the text based on the selection number
	selectionHightlight(levelSelectionNumber);

	// Check if cool down time is greater than 0.0f
	if (levelMenuCooldownTime > 0.0f)
	{
		// Decrement cooldown time by time increment dt
		levelMenuCooldownTime -= dt;
	}

	// Check if menu cool down time is less that or equal to 0.0f
	if (levelMenuCooldownTime <= 0.0f)
	{
		canMakeChoice = true;

		// Check if user has pressed (UP ARROW)
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			// Invoke moveUp() function
			moveUp();
		}

		// Check if user has pressed (DOWN ARROW)
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			// Invoke moveDown() function
			moveDown();
		}
	}

	if (canMakeChoice = true)
	{
		// Enter Debug Room
		if (Keyboard::isKeyPressed(Keyboard::F1))
		{
			// Change scene to the debug scene
			Engine::ChangeScene(&debugScene);
		}

		// User Chooses a selection
		if (Keyboard::isKeyPressed(Keyboard::Enter))
		{

			// New Game
			if (levelSelectionNumber == 0)
			{
				// Start the game from level 1
				Engine::ChangeScene(&level1);
			}
			// Continue Game
			else if (levelSelectionNumber == 1)
			{
				// Start the game from level 1
				Engine::ChangeScene(&level2);
			}
			// Options
			else if (levelSelectionNumber == 2)
			{
				// Start the game from level 1
				Engine::ChangeScene(&level3);
			}
			// Credits
			else if (levelSelectionNumber == 3)
			{
				// Start the game from level 1
				Engine::ChangeScene(&level4);
			}
			// Quit game
			else if (levelSelectionNumber == 4)
			{
				// Start the game from level 1
				Engine::ChangeScene(&level5);
			}
		}
	}
	

	// Update the scene
	Scene::Update(dt);
}

// Selection Highlight function
//
// Function used to highlight text that has been selected
// by the user. If selection number matches the 
// menu item index number, the text is highlighted.
void ContinueScene::selectionHightlight(int selectionNumber)
{
	for (int i = 0; i < MAX_MENU_ITEMS; i++)
	{
		//Obtain the entity at index i
		auto text = _levelMenu[i];

		// Obtain vector of text components
		auto textComps = text->get_components<TextComponent>();

		// As there is only one texture component, obtain the 
		// texture component at position 0 of the vector
		auto textComp = textComps[0];

		// If value of i matches the selection number
		if (i == selectionNumber)
		{
			// Set Text Component to white
			textComp->setColour(Color(255, 255, 255));

			// Set bold
			textComp->textBold();
		}
		//Else
		else
		{
			// Set colour to grey
			textComp->setColour(Color(110, 110, 110));

			// Set text to bold
			textComp->textRegular();
		}
	}
}

// Move Up function
void ContinueScene::moveUp()
{
	// Decrement the selection number
	levelSelectionNumber--;

	// Check that the selection number does not subceed minimum index number of the menu array
	if (levelSelectionNumber < 0)
	{
		// Set selection number to 0
		levelSelectionNumber = 0;
	}

	// Set menu cool down to full time
	levelMenuCooldownTime = defaultLevelMenuCooldownTime;
}

// Move Down function
void ContinueScene::moveDown()
{
	// Increment the selection index number
	levelSelectionNumber++;

	// Check that the selection number does not exceed the maximum index number of the menu array
	if (levelSelectionNumber > 4)
	{
		// Set the selection number to the maximum index number of the menu array
		levelSelectionNumber = 4;
	}

	// Set menu cool down to full time
	levelMenuCooldownTime = defaultLevelMenuCooldownTime;
}
