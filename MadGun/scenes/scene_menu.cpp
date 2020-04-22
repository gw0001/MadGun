/*
 * GAMES ENGINEERING - COURSEWORK
 * -------------------------------------
 * MadGun: Gears and Blood
 * -------------------------------------
 * Franceso Fico - 40404272
 * Graeme White - 40415739
 * -------------------------------------
 * Code Author(s): G. White
 * Date Created: 14/03/2020
 * Date Last Modified: 15/04/2020
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

shared_ptr<Entity> screenText;

shared_ptr<TextComponent> txt;

// Load Function
//
// Function loads required entities for the menu scene
void MenuScene::Load() 
{
	cout << "Menu Load \n";

	// Make an empty entity
	screenText = makeEntity();

	// Apply a text component to the entity
	txt = screenText->addComponent<TextComponent>("This is a text component");

	// Set text component to red colour
	txt->setColour(Color::Red);

	txt->setCharacterSize(32.0);

	//auto moreText = makeEntity();

	//auto moreTxt = moreText->addComponent<TextComponent>("Oh God, more text...");

	//moreTxt->textItalic();

	////open the soundtrack file and plays it
	//music0.openFromFile("res/audio/music/0_menu.ogg");
	//music0.play();

	//// Output menu load message to console
	//cout << "Menu Load \n";
	//{
	//	// Text entity
	//	auto txt = makeEntity();

	//	// Add Text component
	//	auto t = txt->addComponent<TextComponent>("MADGUN: GEARS AND BLOOD\nDEBUG VERSION\n1 - Level 1\n2 - Level 2\n3 - Level 3\nSpace - Debug Room");
	//}

	//// Set loaded to true
	//setLoaded(true);
}

// Update Function
//
// Function updates the menu scene
void MenuScene::Update(const double& dt) 
{
	// Set back to normal 
	if (Keyboard::isKeyPressed(Keyboard::Num1))
	{
		txt->setColour(Color::Red);
		txt->setFont("arial.ttf");
		txt->setCharacterSize(32.0f);
		txt->setLetterSpacing(1.0f);
		txt->setPosition(Vector2f(0.0f, 0.0f));
		txt->setTextOrigin(Vector2f(0.0f, 0.0f));

		txt->textRegular();
	}

	// Change to gotham font
	if (Keyboard::isKeyPressed(Keyboard::Num2))
	{
		txt->setFont("gotham.ttf");
	}


	if (Keyboard::isKeyPressed(Keyboard::Num3))
	{
		txt->setCharacterSize(100.0f);
	}

	if (Keyboard::isKeyPressed(Keyboard::Num4))
	{
		txt->textUnderlined();
	}

	if (Keyboard::isKeyPressed(Keyboard::Num5))
	{
		txt->textBold();
	}
	if (Keyboard::isKeyPressed(Keyboard::Num6))
	{
		txt->textItalic();
	}

	if (Keyboard::isKeyPressed(Keyboard::Num7))
	{
		txt->setPosition(Vector2f(gameWidth / 2.0f, gameHeight / 2.0f));
	}

	if (Keyboard::isKeyPressed(Keyboard::Num8))
	{
		float width = txt->getTextWidth();

		cout << "Text width: " << width << endl;
	}

	if (Keyboard::isKeyPressed(Keyboard::Num9))
	{
		float height = txt->getTextHeight();

		cout << "Text height: " << height << endl;
	}

	if (Keyboard::isKeyPressed(Keyboard::Num0))
	{
		txt->centreOrigin();
	}



	//// Output menu update to the console - Will cause FPS to drop when enabled
	////cout << "Menu Update "<<dt<<"\n";

	//// Set camera to target the centre of the menu screen
	//Renderer::setCameraTarget(Vector2f(gameWidth / 2.0f, gameHeight / 2.0f));

	//// Check if user presses 1
	//if (Keyboard::isKeyPressed(Keyboard::Num1))
	//{
	//	music0.stop();
	//	// Change scene to Level 1
	//	Engine::ChangeScene(&level1);
	//}

	//// Check if user presses 2
	//if (Keyboard::isKeyPressed(Keyboard::Num2))
	//{
	//	music0.stop();
	//	// Change scene to Level 2
	//	Engine::ChangeScene(&level2);
	//}

	//// Check if user presses 3
	//if (Keyboard::isKeyPressed(Keyboard::Num3))
	//{
	//	music0.stop();
	//	// Change scene to Level 3
	//	Engine::ChangeScene(&level3);
	//}

	//// Check if user presses Space bar
	//if (Keyboard::isKeyPressed(Keyboard::Space))
	//{
	//	music0.stop();
	//	// Change scene to Level 1
	//	Engine::ChangeScene(&debugScene);
	//}

	// Update the scene
	Scene::Update(dt);
}
