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
 * Date Last Modified: 27/04/2020
 * -------------------------------------
 * ENDING SCENE - scene_ending.cpp
 *
 * Ending Scene for MadGun
 */

// Libraries
#include "scene_ending.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Window/Joystick.hpp>

// Component libraries
#include "../components/cmp_text.h"

// Credits scene timer
float endingSceneTimer;

// Credits scene duration
float endingSceneDuration = 10.0f;



// Entity shared Pointers
shared_ptr<Entity> message1, message2, message3, message4;

// Text Component Shared pointers
shared_ptr<TextComponent> message1text, message2text, message3text, message4text;

// Load Function
//
// Function loads required entities for the ending scene
void EndingScene::Load() 
{
	// Message to console
	cout << "Ending Load Load \n";

	// Initialise timer to 0
	endingSceneTimer = 0.0f;

	// Create entity
	message1 = makeEntity();

	// Assign text component
	message1text = message1->addComponent<TextComponent>("SUBJECT: MADGUN");

	// Set font to Gotham.ttf
	message1text->setFont("gotham.ttf");

	// Set character size to 45.0f
	message1text->setCharacterSize(45.0f);

	// Set text to Bold
	message1text->textBold();

	// Set Position of text
	message1text->setPosition(Vector2f(275.0f, 50.0f));



	// Create entity
	message2 = makeEntity();

	// Assign text component
	message2text = message1->addComponent<TextComponent>("STATUS: Trials concluded. Awaiting further assignment...");

	// Set font to Gotham.ttf
	message2text->setFont("gotham.ttf");

	// Set character size to 45.0f
	message2text->setCharacterSize(45.0f);

	// Set text to Bold
	message2text->textBold();

	// Set Position of text
	message2text->setPosition(Vector2f(275.0f, 150.0f));


	// Create entity
	message3 = makeEntity();

	// Assign text component
	message3text = message1->addComponent<TextComponent>("\"So, the prototype made it through... It could have gone better in some places\nbut it'll do for now...\"");

	// Set font to Gotham.ttf
	message3text->setFont("gotham.ttf");

	// Set character size to 45.0f
	message3text->setCharacterSize(30.0f);

	// Set text to Bold
	message3text->textBold();

	// Set Position of text
	message3text->setPosition(Vector2f(300.0f, 800.0f));


	// Create entity
	message4 = makeEntity();

	// Assign text component
	message4text = message1->addComponent<TextComponent>("\"I guess we'll have to wait see what the future holds for the MadGun project...\"");

	// Set font to Gotham.ttf
	message4text->setFont("gotham.ttf");

	// Set character size to 45.0f
	message4text->setCharacterSize(30.0f);

	// Set text to Bold
	message4text->textBold();

	// Set Position of text
	message4text->setPosition(Vector2f(300.0f, 875.0f));

}

// Update Function
//
// Function updates the ending scene
void EndingScene::Update(const double& dt) 
{
	// Chekc if ending scene timer is less than the ending scene duration
	if (endingSceneTimer < endingSceneDuration)
	{
		// Incremend timer by time slice
		endingSceneTimer += dt;
	}

	// Chekc if ending scene timer is greater than, or equal to the ending scene duration
	if (endingSceneTimer >= endingSceneDuration)
	{
		// Change scene to credits scene
		Engine::ChangeScene(&creditsScene);
	}

	// Update the scene
	Scene::Update(dt);
}