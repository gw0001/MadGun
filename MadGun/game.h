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
 * Date Last Modified: 16/04/2020
 * -------------------------------------
 * GAME - game.h
 *
 * Header file for the game containing
 * shared variables
 *
 */

// Libraries
#pragma once
#include "scenes/scene_menu.h"
#include "scenes/scene_level1.h"
#include "scenes/scene_level2.h"
#include "scenes/scene_level3.h"
#include "scenes/scene_debug.h"

// MenuScene object
extern MenuScene menu;

// Level 1 Scene object
extern Level1Scene level1;

// Level 2 Scene Object
extern Level2Scene level2;

// Level 3 Scene Object
extern Level3Scene level3;

// Debug Scene - For testing
extern DebugScene debugScene;

// Game Width
constexpr int gameWidth = 1920;

// Game Height
constexpr int gameHeight = 1080;

// Game Zoom
constexpr float gameZoom = 1.0f;

// Menu Zoom
constexpr float menuZoom = 1.0f;
