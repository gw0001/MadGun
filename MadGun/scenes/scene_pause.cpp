/*
 * GAMES ENGINEERING - COURSEWORK
 * -------------------------------------
 * MadGun: Gears and Blood
 * -------------------------------------
 * Francesco Fico - 40404272
 * Graeme White - 40415739
 * -------------------------------------
 * Code Author(s): G. White, F. Fico
 * Date Created: 14/03/2020
 * Date Last Modified: 23/04/2020
 * -------------------------------------
 * Pause SCENE - pause_menu.cpp
 *
 * Pause menu for MadGun
 */


 // Libraries
#include "scene_pause.h"
#include "scene_level2.h"
#include "scene_level2.h"
#include "scene_level2.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <SFML/Window/Joystick.hpp>


// Set selection number to 0
int _selectionPause = 0;

void PauseScene::Load() 
{

    // Message to console
    cout << "Pause Load \n";

    // Title
    {
        // Create title entity
        _pauseTitle = makeEntity();

        // Add Text Component
        auto titleText = _pauseTitle->addComponent<TextComponent>("PAUSE");

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

}

void PauseScene::Update(const double& dt) 
{
    if (Keyboard::isKeyPressed(Keyboard::Return) || sf::Joystick::isButtonPressed(0, 1)) 
    {
        cout << "try to resume";
        if (Scene::lvl1)
        {
            cout << "Level1 resumed";
            Engine::ResumeScene((Scene*)&level1);
            Level1Scene*isPaused = false;
        }else 
        if (Scene::lvl2)
        {
            cout << "Level2 resumed";
            Engine::ResumeScene((Scene*)&level2);
        }else
        if (Scene::lvl2)
        {
            cout << "Level3 resumed";
            Engine::ResumeScene((Scene*)&level3);
        }              
    }
}