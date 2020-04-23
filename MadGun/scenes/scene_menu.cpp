/*
 * GAMES ENGINEERING - COURSEWORK
 * -------------------------------------
 * MadGun: Gears and Blood
 * -------------------------------------
 * Franceso Fico - 40404272
 * Graeme White - 40415739
 * -------------------------------------
 * Code Author(s): G. White, F. Fico
 * Date Created: 14/03/2020
 * Date Last Modified: 23/04/2020
 * -------------------------------------
 * MENU SCENE - scene_menu.cpp
 *
 * Main menu for MadGun
 */

// Libraries
#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Window/Joystick.hpp>

//Level soundtrack
sf::Music music0;

// Set selection number to 0
int _selectionNumber = 0;

// Load Function
//
// Function loads required entities for the menu scene
void MenuScene::Load() 
{
	// Message to console
	cout << "Menu Load \n";

	//open the soundtrack file
	music0.openFromFile("res/audio/music/0_menu.ogg");

	// play background music
	music0.play();

	// Title
	{
		// Create title entity
		_gameTitle = makeEntity();

		// Add Text Component
		auto titleText = _gameTitle->addComponent<TextComponent>("MADGUN");

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

	// Subtitle
	{
		// Create subtitlte text entity
		_gameSubtitle = makeEntity();

		// Add text component to subtitle
		auto subtitleText = _gameSubtitle->addComponent<TextComponent>("GEARS AND BLOOD");
		
		// Set font to Gotham
		subtitleText->setFont("gotham.ttf");

		// Set character size to 34.0f
		subtitleText->setCharacterSize(34.0f);

		// Set Letter Spacing to 14.9f
		subtitleText->setLetterSpacing(14.9f);

		// Set text colour to white
		subtitleText->setColour(Color::White);

		// Set position of subtitle
		subtitleText->setPosition(Vector2f(40.0f, 160.0f));
	}

	// Menu Items
	{
		// Create entities in menu array
		{
			// Iterate over all elements of menu entity array
			for (int i = 0; i < MAX_MENU_ITEMS; i++)
			{
				// Make menu item entity
				_menu[i] = makeEntity();
			}
		}

		// Apply text and properties to each menu item
		for (int i = 0; i < MAX_MENU_ITEMS; i++)
		{
			// Add text component with blank string to menu item at position i
			auto menuItem = _menu[i]->addComponent<TextComponent>();

			// If i is 0
			if (i == 0)
			{
				// Change text to "New Game"
				menuItem->setText("NEW GAME");
			}
			// If i is 1
			else if (i == 1)
			{
				// Change text to "Continue Game"
				menuItem->setText("CONTINUE GAME");
			}
			// If i is 2
			else if (i == 2)
			{
				// Change text to "Options"
				menuItem->setText("OPTIONS");
			}
			// If i is 3
			else if (i == 3)
			{
				// Change text to "Credits"
				menuItem->setText("CREDITS");
			}
			// If i is 4
			else if (i == 4)
			{
				// Change text to "Quit Game"
				menuItem->setText("QUIT GAME");
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
// Function updates the menu scene
void MenuScene::Update(const double& dt) 
{
	// Highlight the text based on the selection number
	selectionHightlight(_selectionNumber);

	// Select "New Game"
	if (Keyboard::isKeyPressed(Keyboard::Num1))
	{
		// Set selection number to 0
		_selectionNumber = 0;
	}

	// Select "Continue" 
	if (Keyboard::isKeyPressed(Keyboard::Num2))
	{
		// Set selection number to 1
		_selectionNumber = 1;
	}

	// Select "Options"
	if (Keyboard::isKeyPressed(Keyboard::Num3))
	{
		// Set selection number to 2
		_selectionNumber = 2;
	}

	// Set "Credits"
	if (Keyboard::isKeyPressed(Keyboard::Num4))
	{
		// Set selection number to 3
		_selectionNumber = 3;
	}

	// Select "Quit Game"
	if (Keyboard::isKeyPressed(Keyboard::Num5))
	{
		// Set selection number to 4
		_selectionNumber = 4;
	}

	// User presses enter
	if (Keyboard::isKeyPressed(Keyboard::Enter))
	{
		// New Game
		if (_selectionNumber == 0)
		{
			// Stop music
			music0.stop();

			// Start the game from level 1
			Engine::ChangeScene(&level1);
		}
		// Continue Game
		else if (_selectionNumber == 1)
		{
			// Continue game screen
		}
		// Options
		else if (_selectionNumber == 2)
		{
			// Options Screen
		}
		// Credits
		else if (_selectionNumber == 3)
		{
			// Credits screen
		}
		// Quit game
		else if (_selectionNumber == 4)
		{
			// Quit Game
			Engine::quitGame();
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
void MenuScene::selectionHightlight(int selectionNumber)
{
	for (int i = 0; i < MAX_MENU_ITEMS; i++)
	{
		//Obtain the entity at index i
		auto text = _menu[i];

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
