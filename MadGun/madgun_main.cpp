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
 * Date Last Modified: 14/04/2020
 * -------------------------------------
 * MAIN - main.cpp
 *
 * Main file for the MadGun game.
 *
 */

// Libraries
#include "engine.h"
#include "game.h"
#include "scenes/scene_menu.h"

// Using Namespace
using namespace std;

// Intro Scene
IntroScene intro;

// Menu Scene
MenuScene menu;

// Continue scene
ContinueScene continueScene;

// Options Scene
HowToScene howToScene;

// Credits Scene
CreditsScene creditsScene;

// Ending Scene
EndingScene endingScene;

// Level 1
Level1Scene level1;

// Level 2
Level2Scene level2;

// Level 3
Level3Scene level3;

// Level 4
Level4Scene level4;

// Level 5
Level5Scene level5;

// Debug Scene
DebugScene debugScene;


// Main function
//
// First function invoked when program starts
int main() 
{
	// Start game from menu screen
	Engine::Start(gameWidth, gameHeight, "MadGun: Gears and Blood",&howToScene);
}