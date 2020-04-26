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
 * TEXT COMPONENT - cmp_text.cpp
 *
 * Text component
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
void TextComponent::setText(const string& str) 
{
	// Set string
	_string = str;

	// Set text string
	_text.setString(_string);
}

// Set Font Function
//
// Function to set the font of a text component
void TextComponent::setFont(string aFont)
{
	// Set font to desired font
	_font = Resources::get<Font>(aFont);

	// Set text font
	_text.setFont(*_font);
}

// Set Position Function
//
// Function for setting the position of a 
// text component
void TextComponent::setPosition(Vector2f aPosition)
{
	// Set position of the text
	_text.setPosition(aPosition);
}

//Vector2f TextComponent::getLocalBounds()
//{
//	_text.getLocalBounds();
//	return rectSiz;
//}

// Set Character Size function
//
// Function sets the character size of the text
// component
void TextComponent::setCharacterSize(float charSize)
{
	// Set Character size of text
	_text.setCharacterSize(charSize);
}

// Set Colour Function
//
// Function sets the colour of the text component
void TextComponent::setColour(Color colour)
{
	// Set Text colour
	_text.setColor(colour);
}

// Set Letter Spacing
//
// Function Sets the letter spacing of a text
// component
void TextComponent::setLetterSpacing(float spacing)
{
	// Set spacing of text
	_text.setLetterSpacing(spacing);
}

// Text Bold Function
//
// Function sets the style of the text component
// to Bold
void TextComponent::textBold()
{
	// Set text to bold style
	_text.setStyle(Text::Bold);
}

// Text Italic Function
//
// Function sets the style of the text component
// to Italic
void TextComponent::textItalic()
{
	// Set text to italic style
	_text.setStyle(Text::Italic);
}

// Text Italic Function
//
// Function sets the style of the text component
// to Underlined
void TextComponent::textUnderlined()
{
	// Set text to underlined style
	_text.setStyle(Text::Underlined);
}

// Text Regular Function
//
// Function sets the style of the text component
// to Regular
void TextComponent::textRegular()
{
	// Set text to regular style
	_text.setStyle(Text::Regular);
}