/*
 * GAMES ENGINEERING - COURSEWORK
 * -------------------------------------
 * MadGun: Gears and Blood
 * -------------------------------------
 * Franceso Fico - 40404272
 * Graeme White - 40415739
 * -------------------------------------
 * Code Author(s): G. White
 * Date Created: 02/03/2020
 * Date Last Modified: 15/03/2020
 * -------------------------------------
 * MAIN - main.cpp
 *
 * Main file for the MadGun game.
 *
 * Currently populated with boilerplate 
 * platformer code from practicals
 */

// Libraries
#include "engine.h"
#include "game.h"
#include "scenes/scene_menu.h"

// Using Namespace
using namespace std;

// Menu Scene
MenuScene menu;

// Level 1
Level1Scene level1;

// Level 2
Level2Scene level2;

// Level 3
Level3Scene level3;

// Game Window width
int gameWidth = 1280;

// Game Window height
int gameHeight = 720;


// Main function
//
// First function invoked when program starts
int main() 
{
	// Start game from menu screen
	Engine::Start(gameWidth, gameHeight, "MadGun: Gears and Blood",&menu);
}