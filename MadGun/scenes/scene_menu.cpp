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
 * Date Last Modified: 27/04/2020
 * -------------------------------------
 * MENU SCENE - scene_menu.cpp
 *
 * Main menu for MadGun
 */

// Libraries
#include "scene_menu.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Window/Joystick.hpp>
#include "system_resources.h"

// Component libraries
#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"

//Level soundtrack
sf::Music music0;

// Set selection number to 0
int selectionNumber;

// Menu selection change boolean
bool menuSelectionChanged = false;

// Default cooldown time for changing menu selection
float defaultMenuCooldownTime = 0.2f;

// Menu Cool Down time initialised to 0.0f
float menuCooldownTime;

// Load Function
//
// Function loads required entities for the menu scene
void MenuScene::Load() 
{
	// Message to console
	cout << "Menu Load \n";

	// Set Camera position to the middle of the window screen
	Renderer::setCameraTarget(Vector2f(gameWidth / 2, gameHeight / 2));

	// Inistialise Menu
	selectionNumber = 0;

	// Initialise the menu cooldown time to 0.5
	menuCooldownTime = 0.5f;

	//open the soundtrack file
	music0.openFromFile("res/audio/music/0_menu.ogg");

	// play background music
	music0.play();

	// Loop background music
	music0.setLoop(true);

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
				// Change text to "Level Select"
				menuItem->setText("LEVEL SELECT");
			}
			// If i is 2
			else if (i == 2)
			{
				// Change text to "How to Play"
				menuItem->setText("HOW TO PLAY");
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

	// MadGun image
	{
		// Create entity
		auto e = makeEntity();

		// Assing Sprite component
		auto madgun = e->addComponent<SpriteComponent>();

		// MadGun texture shared pointer
		shared_ptr<Texture> madgunTexture;

		// Load madgun texture
		madgunTexture = Resources::get<Texture>("playerBig.png");

		// Set Textrue
		madgun->setTexure(madgunTexture);

		// Set position
		e->setPosition(Vector2f(gameWidth / 2.0f, 0.0f));
	}
}

// Update Function
//
// Function updates the menu scene
void MenuScene::Update(const double& dt) 
{
	// Highlight the text based on the selection number
	selectionHightlight(selectionNumber);

	// Check if cool down time is greater than 0.0f
	if (menuCooldownTime > 0.0f)
	{
		// Decrement cooldown time by time increment dt
		menuCooldownTime -= dt;
	}

	// Check if menu cool down time is less that or equal to 0.0f
	if (menuCooldownTime <= 0.0f)
	{
		// Check if user has pressed up arrow, or move the analogue stick up
		if (Keyboard::isKeyPressed(Keyboard::Up) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) == -100)
		{
			// Invoke moveUp() function
			moveUp();
		}

		// Check if user has pressed down arrow, or moved the analogue stick down
		if (Keyboard::isKeyPressed(Keyboard::Down) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) == 100)
		{
			// Invoke moveDown() function
			moveDown();
		}
	}

	// Check that the menu cooldown time is less than or equal to 0.0f
	if (menuCooldownTime <= 0.0f)
	{
		// User Chooses a selection
		if (Keyboard::isKeyPressed(Keyboard::Enter) || sf::Joystick::isButtonPressed(0, 0))
		{
			// Stop music
			music0.stop();

			// New Game
			if (selectionNumber == 0)
			{
				// Start the game from level 1
				Engine::ChangeScene(&level1);
			}
			// Continue Game
			else if (selectionNumber == 1)
			{
				// Continue game screen
				Engine::ChangeScene(&continueScene);
			}
			// Options
			else if (selectionNumber == 2)
			{
				// Options Screen
				Engine::ChangeScene(&howToScene);
			}
			// Credits
			else if (selectionNumber == 3)
			{
				// Credits screen
				Engine::ChangeScene(&creditsScene);
			}
			// Quit game
			else if (selectionNumber == 4)
			{
				// Quit Game
				Engine::quitGame();
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

// Move Up function
void MenuScene::moveUp()
{
	// Decrement the selection number
	selectionNumber--;

	// Check that the selection number does not subceed minimum index number of the menu array
	if (selectionNumber < 0)
	{
		// Set selection number to 0
		selectionNumber = 0;
	}

	// Set menu cool down to full time
	menuCooldownTime = defaultMenuCooldownTime;
}

// Move Down function
void MenuScene::moveDown()
{
	// Increment the selection index number
	selectionNumber++;

	// Check that the selection number does not exceed the maximum index number of the menu array
	if (selectionNumber > MAX_MENU_ITEMS - 1)
	{
		// Set the selection number to the maximum index number of the menu array
		selectionNumber = MAX_MENU_ITEMS - 1;
	}

	// Set menu cool down to full time
	menuCooldownTime = defaultMenuCooldownTime;
}
