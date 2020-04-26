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
 * Pause Menu - pause_menu.h
 *
 *
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <ecm.h>
#include "../game.h"
#include "engine.h"

//Namespaces

using namespace std; // Standard namespace
using namespace sf; // SFML namespace

//PAUSE MENU CLASS

class PauseMenu : public Component
{
protected:

    // New shape declaration
    RectangleShape _background;    

public:
    // Blank pause menu contructor (deleted)
    PauseMenu() = delete;

    // Pause Menu constructor
    explicit PauseMenu(Entity* p);

    // Pause Menu deconstructor
    ~PauseMenu() override = default;

    //Functions

    //Update
    void update(double dt) override;
    
    // Render
    void render() override;

    //Shape setPosition
    void setPosition(Vector2f);
    
    

    
};