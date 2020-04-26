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
 * Date Last Modified: 25/04/2020
 * -------------------------------------
 * INTRO SCENE - scene_intro.cpp
 *
 * Intro scene for MadGun game
 */

// Libraries
#include "scene_intro.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Window/Joystick.hpp>
#include "system_resources.h"

// Component libraries
#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"

// Intro Timer
float introTimer = 0.0f;

// Intro Scene Duration
float introSceneDuration = 7.0f;

// Fade In Timer
float fadeInTimer = 0.0f;

// Fade Out Timer
float fadeOutTimer = 0.0f;

// Fade Duration
float fadeDuration = 1.5f;

// Texture Scale Value
float scaleValue = 3.0f;

// Intro Logo shared pointer
shared_ptr<Entity> introLogo;

// Fade rectangle shared pointer
shared_ptr<Entity> fadeRectangle;

// Rectangle shape fade pointer
shared_ptr<ShapeComponent> rectangleShape;

Texture logoTexture;

// Load Function
//
// Function loads required entities for the intro scene
void IntroScene::Load() 
{
	// Message to console
	cout << "Intro Load \n";

	// Set camera to the centre of the screen
	Renderer::setCameraTarget(Vector2f(gameWidth / 2.0f, gameHeight / 2.0f));

	// Create Logo entity
	introLogo = makeEntity();
	
	// Add shape component to entity
	auto logo = introLogo->addComponent<ShapeComponent>();

	// Load logo texture from file
	logoTexture.loadFromFile("res/img/sfmlLogo.png");

	// Obtain the width of the texture
	float textureWidth = logoTexture.getSize().x;

	// Obtian the height of the texture
	float textureHeight = logoTexture.getSize().y;

	// Set shape of logo to a rectangle shape
	logo->setShape<RectangleShape>(Vector2f(textureWidth, textureHeight));

	// Set logo shape to the texture of the SFML logo
	logo->getShape().setTexture(&logoTexture);

	// Set origin of the shape to half the width and half the height of the texture
	logo->getShape().setOrigin(Vector2f(textureWidth /2, textureHeight / 2));

	// Set the position of the logo to half the width and half the height of the game window
	logo->getShape().setPosition(Vector2f(gameWidth / 2.0f, gameHeight / 2.0f));

	// Scale the logo
	logo->getShape().setScale(Vector2f(1/scaleValue, 1/scaleValue));

	// Add text component to the logo
	auto text = introLogo->addComponent<TextComponent>("Created with");

	// Set the position of the text above the logo
	text->setPosition(Vector2f(-250.0f, -120.0f));

	// Set letter spacing
	text->setLetterSpacing(2.5f);

	// Set text to itallic
	text->textItalic();

	// Create Fade Rectangle entity
	fadeRectangle = makeEntity();

	// Add shape component
	rectangleShape = fadeRectangle->addComponent<ShapeComponent>();

	// Set shape to rectangle shape with the width and height of the game screen
	rectangleShape->setShape<RectangleShape>(Vector2f(gameWidth, gameHeight));

	// Set fill colour to black
	rectangleShape->getShape().setFillColor(Color::Black);

	// Set the origin of the rectangle to half the width and height of the game window
	rectangleShape->getShape().setOrigin(gameWidth / 2.0f, gameHeight / 2.0f);
}

// Update Function
//
// Function updates the intro scene
void IntroScene::Update(const double& dt) 
{
	// Check if timer is less that the scene duration
	if (introTimer < introSceneDuration)
	{
		// Incremend timer by time slice
		introTimer += dt;
	}

	// Check if 1 second has passed
	if (introTimer >= 1.0f && introTimer < 5.0f)
	{
		// Increment Fade In Timer
		fadeInTimer += dt;

		// Determine the alpha value (will decrease over time)
		float alpha = 255.0f - (fadeInTimer * 255.0f/ fadeDuration);

		// Check if the alpha value calculated is less than 0
		if (alpha < 0.0f)
		{
			// Set alpha to 0
			alpha = 0.0f;
		}

		// Set the fill colour of the fade rectangle shape
		rectangleShape->getShape().setFillColor(Color(0, 0, 0, alpha));
	}

	// Check that 5 seconds have passed
	if (introTimer >= 5.0f && introTimer < introSceneDuration)
	{
		// Increment Fade Out Timer
		fadeOutTimer += dt;

		// Determine the alpha value (will increase over time)
		float alpha = 0.0f + (fadeOutTimer * 255.0f / fadeDuration);

		// Check if the alpha exceeds 255
		if (alpha > 255.0f)
		{
			// Set alpha value to 255
			alpha = 255.0f;
		}

		// Set the fill colour of the fade rectangle shape
		rectangleShape->getShape().setFillColor(Color(0, 0, 0, alpha));
	}

	// Check if timer is greater than, or equal to the scene duration
	if (introTimer >= introSceneDuration)
	{
		// Change to the menu scene
		Engine::ChangeScene(&menu);
	}
	
	// Update the scene
	Scene::Update(dt);
}
