#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "engine.h"
#include <iostream>
#include <ecm.h>
#include <future>
#include <maths.h>
#include <mutex>
#include <string>

using namespace std; // Standard namespace
using namespace sf; // SFML namespace

class PauseMenu
{
private:
    sf::RectangleShape background;
    sf::RectangleShape container;
    // Game title entity
    shared_ptr<Entity> _gameTitle;

public:
    PauseMenu(sf::RenderWindow& window);
    virtual ~PauseMenu();

    //Functions

    void Update();
    void Render(sf::RenderTarget& target);
};