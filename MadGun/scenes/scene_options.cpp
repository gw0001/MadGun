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
 * OPTIONS SCENE - scene_options.cpp
 *
 * Options Menu for MadGun
 */

// Libraries
#include "scene_options.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Window/Joystick.hpp>

// Component libraries
#include "../components/cmp_text.h"



//// Set selection number to 0
//int selectionNumber;
//
//// Menu selection change boolean
//bool menuSelectionChanged = false;
//
//// Default cooldown time for changing menu selection
//float defaultMenuCooldownTime = 0.25f;
//
//// Menu Cool Down time initialised to 0.0f
//float menuCooldownTime = 0.0f;


// Load Function
//
// Function loads required entities for the menu scene
void OptionsScene::Load() 
{
	// Message to console
	cout << "Options Load \n";

	auto e = makeEntity();

	auto txt = e->addComponent<TextComponent>("The Options menu for controller remapping, resolution, and VSync options will go here");

	// Set camera position to the middle of the screen
	Renderer::setCameraTarget(Vector2f(gameWidth / 2, gameHeight / 2));
}

// Update Function
//
// Function updates the menu scene
void OptionsScene::Update(const double& dt) 
{
	// CODE GOES HERE
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		Engine::ChangeScene(&menu);
	}
	
	// Update the scene
	Scene::Update(dt);
}

//// Selection Highlight function
////
//// Function used to highlight text that has been selected
//// by the user. If selection number matches the 
//// menu item index number, the text is highlighted.
//void OptionsScene::selectionHightlight(int selectionNumber)
//{
//	for (int i = 0; i < MAX_MENU_ITEMS; i++)
//	{
//		//Obtain the entity at index i
//		auto text = _menu[i];
//
//		// Obtain vector of text components
//		auto textComps = text->get_components<TextComponent>();
//
//		// As there is only one texture component, obtain the 
//		// texture component at position 0 of the vector
//		auto textComp = textComps[0];
//
//		// If value of i matches the selection number
//		if (i == selectionNumber)
//		{
//			// Set Text Component to white
//			textComp->setColour(Color(255, 255, 255));
//
//			// Set bold
//			textComp->textBold();
//		}
//		//Else
//		else
//		{
//			// Set colour to grey
//			textComp->setColour(Color(110, 110, 110));
//
//			// Set text to bold
//			textComp->textRegular();
//		}
//	}
//}
//
//// Move Up function
//void OptionsScene::moveUp()
//{
//	// Decrement the selection number
//	selectionNumber--;
//
//	// Check that the selection number does not subceed minimum index number of the menu array
//	if (selectionNumber < 0)
//	{
//		// Set selection number to 0
//		selectionNumber = 0;
//	}
//
//	// Set menu cool down to full time
//	menuCooldownTime = defaultMenuCooldownTime;
//}
//
//// Move Down function
//void OptionsScene::moveDown()
//{
//	// Increment the selection index number
//	selectionNumber++;
//
//	// Check that the selection number does not exceed the maximum index number of the menu array
//	if (selectionNumber > MAX_MENU_ITEMS - 1)
//	{
//		// Set the selection number to the maximum index number of the menu array
//		selectionNumber = MAX_MENU_ITEMS - 1;
//	}
//
//	// Set menu cool down to full time
//	menuCooldownTime = defaultMenuCooldownTime;
//}
