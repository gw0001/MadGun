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
#include <SFML/Graphics/Text.hpp>
#include <ecm.h>

#define MAX_NUMBER_OF_ITEMS 3

// Namespaces
using namespace std; // Standard namespace
using namespace sf; // SFML namespace

/*
 * MENU SCENE
 *
 * Menu Scene Class
 */
class MenuScene : public Scene 
{
	public:
		// Menu scene constructor
		MenuScene() = default;

		// Menu scene deconstructor
		~MenuScene() override = default;

		// Load function
		void Load() override;

		// Update function
		void Update(const double& dt) override;
};

class Menu : public Component
{
public:
    Menu() = delete;
    explicit Menu(Entity* p);
    ~Menu() override = default;

    void render() override;

    //void draw(sf::RenderWindow& window);
    void MoveUp();
    void MoveDown();
    int GetPressedItem() { return selectedItemIndex; }

private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text menu[MAX_NUMBER_OF_ITEMS];

};
