/*
 * GAMES ENGINEERING - COURSEWORK
 * -------------------------------------
 * MadGun: Gears and Blood
 * -------------------------------------
 * Francesco Fico - 40404272
 * Graeme White - 40415739
 * -------------------------------------
 * Code Author(s): G. White
 * Date Created: 14/03/2020
 * Date Last Modified: 23/04/2020
 * -------------------------------------
 * MENU SCENE - scene_menu.h
 *
 * Header file Main menu.
 *
 * Currently populated with boilerplate
 * platformer code from practicals
 */


 // Libraries
#pragma once
#include "engine.h"

// Definitions
#define MAX_MENU_ITEMS 5
// Namespaces
using namespace std; // Standard namespace
using namespace sf; // SFML namespace

/*
 * PAUSE SCENE
 *
 * Pause Scene Class
 */
class PauseScene : public Scene
{
public:
    // Menu scene constructor
    PauseScene() = default;

    // Menu scene deconstructor
    ~PauseScene() override = default;

    // Load function
    void Load() override;

    // Update function
    void Update(const double& dt) override;

private:
    //
    int _selectionPause;
    // Game title entity
    shared_ptr<Entity> _pauseTitle;    

    // Menu entity array
    shared_ptr<Entity> _menu[MAX_MENU_ITEMS];

    // Selection Highlight function
    void selectionHightlight(int anInt);



};
