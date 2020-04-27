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
 * CREDITS SCENE - scene_credits.cpp
 *
 * Credits Scene for MadGun
 */

// Libraries
#include "scene_credits.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Window/Joystick.hpp>

// Component libraries
#include "../components/cmp_text.h"

// Heading Text size
float headingSize = 80.0f;

// Standard Text Size
float textSize = 30.0f;

//Level audio variables
sf::Music music6;
sf::SoundBuffer buffer6;
sf::Sound endLvl6;

// Entity shared Pointers
shared_ptr<Entity> creditsHeading, teamMembers, spriteAssets, musicAssets, soundEffectAssets, thankYou, instructions;

// Text Component Shared pointers
shared_ptr<TextComponent> headingText, teamText, spriteText, musicText, soundEffectText, thankYouText, instructionText;

// Load Function
//
// Function loads required entities for the menu scene
void CreditsScene::Load() 
{
	// Message to console
	cout << "Options Load \n";

	// Set camera position to the middle of the screen
	Renderer::setCameraTarget(Vector2f(gameWidth / 2, gameHeight / 2));

	music6.openFromFile("res/audio/music/6_credits.ogg");
	music6.play();
	music6.setLoop(true);

	// Credits Heading
	{
		// Create Credits Heading Entity
		creditsHeading = makeEntity();

		// Add text component
		headingText = creditsHeading->addComponent<TextComponent>("CREDITS");

		// Set font to Gotham.ttf
		headingText->setFont("gotham.ttf");

		// Set character size to 75.0f
		headingText->setCharacterSize(headingSize);

		// Set letter spacing to 10.0f
		headingText->setLetterSpacing(5.0f);

		// Set text to underlined
		headingText->textBold();

		// Set Position of text
		headingText->setPosition(Vector2f(30.0f, 10.0f));

	}
	// Team Members
	{
		// Make Team Members entity
		teamMembers = makeEntity();

		// Apply Text component
		teamText = teamMembers->addComponent<TextComponent>("Created and developed by:\n	Graeme White\n	Francesco Fico");
		
		// Set font to Gotham.ttf
		teamText->setFont("gotham.ttf");

		// Set character size to 75.0f
		teamText->setCharacterSize(textSize);

		// Set text to underlined
		teamText->textItalic();

		// Set Position
		teamText->setPosition(Vector2f(60.0f, 110.0f));
	}

	// Sprite Assets
	{
		// Make Team Members entity
		spriteAssets = makeEntity();

		// Apply Text component
		spriteText = spriteAssets->addComponent<TextComponent>("Sprite Assets:\n	16 x 16 Robot Tile Set and Robots by Robert \"0x72\" Norenberg \n		Available via:- https://0x72.itch.io/16x16-robot-tileset\n\n	Orange Robot and Turret by \" Edu\" \n	Available via: - https://eduuuuu.itch.io/robot-platform-pack\n\n	Developer textures and spikes by Graeme White");

		// Set font to Gotham.ttf
		spriteText->setFont("gotham.ttf");

		// Set character size to 75.0f
		spriteText->setCharacterSize(textSize);

		// Set text to underlined
		spriteText->textItalic();

		// Set Position
		spriteText->setPosition(Vector2f(60.0f, 210.0f));
	}

	// Music
	{
		// Make Team Members entity
		musicAssets = makeEntity();

		// Apply Text component
		musicText = musicAssets->addComponent<TextComponent>("Music Assets:\n	DOS-88 Synthwave Music Library by DOS88\n		Available via:- https://dos88.itch.io/dos-88-music-library");

		// Set font to Gotham.ttf
		musicText->setFont("gotham.ttf");

		// Set character size to 75.0f
		musicText->setCharacterSize(textSize);

		// Set text to underlined
		musicText->textItalic();

		// Set Position
		musicText->setPosition(Vector2f(60.0f, 475.0f));
	}

	// Sound Effects
	{
		// Make Team Members entity
		soundEffectAssets = makeEntity();

		// Apply Text component
		soundEffectText = soundEffectAssets->addComponent<TextComponent>("Sound Effect Assets:\n	8-bit Soundpack by \"SoundsByDane\"\n		Available via:- https://soundsbydane.itch.io/8-bit-sound-pack");

		// Set font to Gotham.ttf
		soundEffectText->setFont("gotham.ttf");

		// Set character size to 75.0f
		soundEffectText->setCharacterSize(textSize);

		// Set text to underlined
		soundEffectText->textItalic();

		// Set Position
		soundEffectText->setPosition(Vector2f(60.0f, 575.0f));
	}

	// Thank You Message
	{
		// Make Team Members entity
		thankYou = makeEntity();

		// Apply Text component
		thankYouText = thankYou->addComponent<TextComponent>("Thanks for playing!");

		// Set font to Gotham.ttf
		thankYouText->setFont("gotham.ttf");

		// Set character size to 75.0f
		thankYouText->setCharacterSize(headingSize);

		// Set text to underlined
		thankYouText->textRegular();

		// Set Position
		thankYouText->setPosition(Vector2f(550.0f, 800.0f));
	}

	// Intruction
	{
		// Make Team Members entity
		instructions = makeEntity();

		// Apply Text component
		instructionText = instructions->addComponent<TextComponent>("Press the \"Escape\" key or the \"B\" button to return to the main menu");

		// Set font to Gotham.ttf
		instructionText->setFont("gotham.ttf");

		// Set character size to 75.0f
		instructionText->setCharacterSize(textSize);

		// Set text to underlined
		instructionText->textBold();

		// Set Position
		instructionText->setPosition(Vector2f(60.0f, gameHeight - headingSize));
	}
}

// Update Function
//
// Function updates the menu scene
void CreditsScene::Update(const double& dt) 
{
	// User Presses escape key or start button
	if (Keyboard::isKeyPressed(Keyboard::Escape) || (sf::Joystick::isButtonPressed(0, 7)))
	{
		// Stop music
		music6.stop();

		// Change scene to the main menu
		Engine::ChangeScene(&menu);
	}
	
	// Update the scene
	Scene::Update(dt);
}