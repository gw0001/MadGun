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

// Update function
//
// Function updates the text component
void TextComponent::update(double dt) {}

// Render function
//
// Function renders the text component
void TextComponent::render() 
{
	// Add text to renderer queue
	Renderer::queue(&_text);
}

// Text Component constructor
TextComponent::TextComponent(Entity* const p, const string& str)
    : Component(p), _string(str) 
{
	// Set String
	_text.setString(_string);

	// Set font to arial
	_font = Resources::get<Font>("arial.ttf");

	// Set text font
	_text.setFont(*_font);
}

// Set Text function
//
// Function sets the text of the text component
void TextComponent::SetText(const string& str) 
{
	// Set string
	_string = str;

	// Set text string
	_text.setString(_string);
}
