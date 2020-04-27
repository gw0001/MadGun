/*
 * GAMES ENGINEERING - COURSEWORK
 * -------------------------------------
 * MadGun: Gears and Blood
 * -------------------------------------
 * Franceso Fico - 40404272
 * Graeme White - 40415739
 * -------------------------------------
 * Code Author(s): G. White, F. Fico
 * Date Created: 23/04/2020
 * Date Last Modified: 23/04/2020
 * -------------------------------------
 * OPTIONS SCENE - scene_options.cpp
 *
 * Options Menu for MadGun
 */

// Libraries
#include "scene_howto.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Window/Joystick.hpp>

// Component libraries
#include "../components/cmp_text.h"

// Load Function
//
// Function loads required entities for the menu scene
void HowToScene::Load() 
{
	// Heading
	{
		// Create entity
		auto e = makeEntity();

		// Add text component
		auto text = e->addComponent<TextComponent>("How To Play");

		// Set font to Gotham.ttf
		text->setFont("gotham.ttf");

		// Set character size to 75.0f
		text->setCharacterSize(75.0f);

		// Set letter spacing to 2.0f
		text->setLetterSpacing(2.0f);

		// Set text to underlined
		text->textBold();

		// Set Position of text
		text->setPosition(Vector2f(30.0f, 10.0f));
	}
	
	// Game Goal description
	{
		// Create entity
		auto e = makeEntity();

		// Add text component
		auto text = e->addComponent<TextComponent>("Help MadGun, the orange robot, navigate through each chamber\nand find the exit. Avoid traps, turrets, and other robots!\n\nIf you are hit by another robot or a bullet, you will have to start again!");

		// Set font to Gotham.ttf
		text->setFont("gotham.ttf");

		// Set character size to 75.0f
		text->setCharacterSize(45.0f);

		// Set text to bold
		text->textBold();

		// Set Position of text
		text->setPosition(Vector2f(30.0f, 100.0f));
	}

	// Keyboard controls heading
	{
		// Create entity
		auto e = makeEntity();

		// Add text component
		auto text = e->addComponent<TextComponent>("Keyboard controls");

		// Set font to Gotham.ttf
		text->setFont("gotham.ttf");

		// Set character size to 75.0f
		text->setCharacterSize(45.0f);

		// Set text to underlined
		text->textUnderlined();

		// Set Position of text
		text->setPosition(Vector2f(30.0f, 375.0f));
	}

	// Keyboard controls
	{
		// Create entity
		auto e = makeEntity();

		// Add text component
		auto text = e->addComponent<TextComponent>("\nMOVE LEFT: Left Arrow\nMOVE RIGHT: Right Arrow\nJUMP: Up Arrow\nRETURN TO MAIN MENU: Escape Key\nMOVE MENU SELECTION UP: Up Arrow\nMOVE MENU SELECTION DOWN: Down Arrow\nCONFIRM SELECTION: Enter");

		// Set font to Gotham.ttf
		text->setFont("gotham.ttf");

		// Set character size to 75.0f
		text->setCharacterSize(30.0f);

		// Set Position of text
		text->setPosition(Vector2f(30.0f, 400.0f));
	}

	// Keyboard controls heading
	{
		// Create entity
		auto e = makeEntity();

		// Add text component
		auto text = e->addComponent<TextComponent>("Xbox/Steam Joypad controls");

		// Set font to Gotham.ttf
		text->setFont("gotham.ttf");

		// Set character size to 75.0f
		text->setCharacterSize(45.0f);

		// Set text to underlined
		text->textUnderlined();

		// Set Position of text
		text->setPosition(Vector2f(gameWidth/2.0f, 375.0f));
	}

	// Keyboard controls
	{
		// Create entity
		auto e = makeEntity();

		// Add text component
		auto text = e->addComponent<TextComponent>("\nMOVE LEFT: Left Analogue Stick (Left)\nMOVE RIGHT: Left Analogue Stick (Right)\nJUMP: A Button\nRETURN TO MAIN MENU: Start Button\nMOVE MENU SELECTION UP: Left Analogue Stick (up)\nMOVE MENU SELECTION DOWN: Left Analogue Stick (down)\nCONFIRM SELECTION: A button");

		// Set font to Gotham.ttf
		text->setFont("gotham.ttf");

		// Set character size to 75.0f
		text->setCharacterSize(30.0f);

		// Set Position of text
		text->setPosition(Vector2f(gameWidth / 2.0f, 400.0f));
	}

	// Instructions
	{
		// Create entity
		auto e = makeEntity();

		// Add text component
		auto text = e->addComponent<TextComponent>("Press \"Escape\" key on the keyboard or press \"Start\" on the controller to return to the main menu");

		// Set font to Gotham.ttf
		text->setFont("gotham.ttf");

		// Set character size to 75.0f
		text->setCharacterSize(30.0f);

		// Set text to bold
		text->textBold();

		// Set Position of text
		text->setPosition(Vector2f(30.0f, 1000.0f));
	}
}

// Update Function
//
// Function updates the menu scene
void HowToScene::Update(const double& dt) 
{
	// User presses escape key or presses start
	if (Keyboard::isKeyPressed(Keyboard::Escape) || (sf::Joystick::isButtonPressed(0, 7)))
	{
		// Return to the menu screen
		Engine::ChangeScene(&menu);
	}
	
	// Update the scene
	Scene::Update(dt);
}
