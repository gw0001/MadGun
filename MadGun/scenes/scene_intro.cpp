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

float introTimer = 0.0f;

float introSceneDuration = 2.0f;



// Load Function
//
// Function loads required entities for the intro scene
void IntroScene::Load() 
{
	// Message to console
	cout << "Intro Load \n";

	auto e = makeEntity();

	auto txt = e->addComponent<TextComponent>("This is the Intro Scene");

	txt->setPosition(Vector2f(100.0f, 500.0f));

	auto entity2 = makeEntity();

	auto sfmlLogo = entity2->addComponent<SpriteComponent>();

	auto tex = Resources::get<Texture>("sfmlLogo.png");

	sfmlLogo->setTexure(tex);


	// Set camera position to the middle of the screen
	Renderer::setCameraTarget(Vector2f(gameWidth / 2, gameHeight / 2));
}

// Update Function
//
// Function updates the intro scene
void IntroScene::Update(const double& dt) 
{
	// CODE GOES HERE
		// CODE GOES HERE
	if (introTimer < introSceneDuration)
	{
		introTimer += dt;
	}


	if (introTimer >= introSceneDuration)
	{
		Engine::ChangeScene(&menu);
	}
	
	// Update the scene
	Scene::Update(dt);
}
