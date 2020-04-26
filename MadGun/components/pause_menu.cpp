/*
 * GAMES ENGINEERING - COURSEWORK
 * -------------------------------------
 * MadGun: Gears and Blood
 * -------------------------------------
 * Francesco Fico - 40404272
 * Graeme White - 40415739
 * -------------------------------------
 * Code Author(s): F. Fico
 * Date Created: 14/03/2020
 * Date Last Modified: 15/03/2020
 * -------------------------------------
 * Pause Menu - pause_menu.cpp
 *
 *
 */

//Libraries

#include "pause_menu.h"
#include "../game.h"
#include <system_renderer.h>
#include <system_resources.h>
#include <LevelSystem.h>

// Update function
//
// Function updates the pause component
void PauseMenu::update(double dt) {}


// Render function
//
// Function renders the pause component
void PauseMenu::render() 
{
	Renderer::queue(&_background);
}

// Pause component constructor
PauseMenu::PauseMenu(Entity* const p)
	: Component(p)
	
{	
    // set size of the shape
	 _background.setSize(sf::Vector2f(gameHeight, gameWidth));
     // set the colour of the shape
	 _background.setFillColor(sf::Color(20, 20, 20, 200));	
     //set the origin of the shape
	 _background.setOrigin(_background.getSize().x / 2.f , _background.getSize().y / 2.f); 	
}


// function to set the position of the shape
void PauseMenu::setPosition(Vector2f cord) 
{
	_background.setPosition(cord);
}





