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
 * Date Last Modified: 15/03/2020
 * -------------------------------------
 * TEXT COMPONENT - cmp_text.cpp
 *
 * Text component
 *
 * Currently populated with boiler plate
 * code from platformer practical
 *
 */

// Libraries
#include "cmp_text.h"
#include <system_renderer.h>
#include <system_resources.h>
#include "../game.h"

// Update function
//
// Function updates the text component
void TextComponent::update(double dt) {}

// Render function
//
// Function renders the text component
void TextComponent::render() 
{
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) 
    {
        // Add text to renderer queue
        Renderer::queue(&_text);
        Renderer::queue(&_sub);
        Renderer::queue(&menu[i]);
    }
}

// Text Component constructor
TextComponent::TextComponent(Entity* const p, const string& str)
    : Component(p), _string(str) 
{
	// Set String
	//_text.setString(_string);

	// Set font to gotham
	_font = Resources::get<Font>("gotham-medium.ttf");

    _text.setString("MADGUN: Gears and Blood");
    _text.setFont(*_font);
    _text.setFillColor(sf::Color::Red);
    _text.setCharacterSize(100);
    _text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    _text.setPosition(gameWidth / 2.0f, 100);
    _text.setOrigin(_text.getLocalBounds().width / 2.0f, _text.getLocalBounds().height / 2.0f);
    
    menu[0].setString("Play:");
    menu[0].setFont(*_font);
    menu[0].setFillColor(sf::Color::White);
    menu[0].setStyle(sf::Text::Bold);
    menu[0].setCharacterSize(48);   
    menu[0].setPosition(gameWidth / 2.0f, gameHeight / 3.0f);
    menu[0].setOrigin(menu[0].getLocalBounds().width / 2.0f, menu[0].getLocalBounds().height / 2.0f);

    
    menu[2].setString("Options:");
    menu[2].setFont(*_font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setStyle(sf::Text::Bold);
    menu[2].setCharacterSize(48);
    menu[2].setPosition(gameWidth / 2.0f, gameHeight / 2.0f);
    menu[2].setOrigin(menu[2].getLocalBounds().width / 2.0f, menu[2].getLocalBounds().height / 2.0f);

    
    menu[1].setString("press return or controller A");
    menu[1].setFont(*_font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setCharacterSize(32);
    menu[1].setPosition(gameWidth / 2.0f, gameHeight / 2.6f);
    menu[1].setOrigin(menu[1].getLocalBounds().width / 2.0f, menu[1].getLocalBounds().height / 2.0f);

    _sub.setString("press tab or controller B");
    _sub.setFont(*_font);
    _sub.setFillColor(sf::Color::White);
    _sub.setCharacterSize(32);
    _sub.setPosition(gameWidth / 2.0f, gameHeight / 1.8f);
    _sub.setOrigin(_sub.getLocalBounds().width / 2.0f, _sub.getLocalBounds().height / 2.0f);

    

    /*selectedItemIndex = 1;*/



}

// Set Text function
//
// Function sets the text of the text component
//void TextComponent::SetText(const string& str) 
//{
//	// Set string
//	_string = str;
//
//	// Set text string
//	_text[2].setString(_string);
//}

//void TextComponent::MoveUp()
//{
//    if (selectedItemIndex - 1 >= 0)
//    {
//        menu[selectedItemIndex].setColor(sf::Color::White);
//        selectedItemIndex--;
//        menu[selectedItemIndex].setColor(sf::Color::Red);
//    }
//}
//
//void TextComponent::MoveDown()
//{
//    if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
//    {
//        menu[selectedItemIndex].setColor(sf::Color::White);
//        selectedItemIndex++;
//        menu[selectedItemIndex].setColor(sf::Color::Red);
//    }
//}
