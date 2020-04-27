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
 * Date Last Modified: 23/04/2020
 * -------------------------------------
 * GAME - game.h
 *
 * Header file for the game containing
 * shared variables
 *
 */

// Libraries
#pragma once
#include "scenes/scene_intro.h"
#include "scenes/scene_menu.h"
#include "scenes/scene_continue.h"
#include "scenes/scene_howto.h"
#include "scenes/scene_ending.h"
#include "scenes/scene_level1.h"
#include "scenes/scene_level2.h"
#include "scenes/scene_level3.h"
#include "scenes/scene_level4.h"
#include "scenes/scene_level5.h"
#include "scenes/scene_debug.h"
#include "scenes/scene_credits.h"

// IntroScene object
extern IntroScene intro;

// MenuScene object
extern MenuScene menu;

// ContinueScene object
extern ContinueScene continueScene;

// OptionsScene object
extern HowToScene howToScene;

// EndingScene object
extern EndingScene endingScene;

// Level 1 Scene object
extern Level1Scene level1;

// Level 2 Scene Object
extern Level2Scene level2;

// Level 3 Scene Object
extern Level3Scene level3;

// Level 3 Scene Object
extern Level4Scene level4;

// Level 3 Scene Object
extern Level5Scene level5;

// Debug Scene object- For testing
extern DebugScene debugScene;

// Credits Scene Object
extern CreditsScene creditsScene;

// Game Width
constexpr int gameWidth = 1920;

// Game Height
constexpr int gameHeight = 1080;
