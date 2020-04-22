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
 * Date Last Modified: 22/04/2020
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

// Set Character Size function
//
// Function sets the character size of the text
// component
void TextComponent::setCharacterSize(float charSize)
{
	_text.setCharacterSize(charSize);
}

// Set Colour Function
//
// Function sets the colour of the text component
void TextComponent::setColour(Color colour)
{
	_text.setColor(colour);
}

// Set Letter Spacing
//
// Function Sets the letter spacing of a text
// component
void TextComponent::setLetterSpacing(float spacing)
{
	_text.setLetterSpacing(spacing);
}

// Text Bold Function
//
// Function sets the style of the text component
// to Bold
void TextComponent::textBold()
{
	_text.setStyle(Text::Bold);
}

// Text Italic Function
//
// Function sets the style of the text component
// to Italic
void TextComponent::textItalic()
{
	_text.setStyle(Text::Italic);
}

// Text Italic Function
//
// Function sets the style of the text component
// to Underlined
void TextComponent::textUnderlined()
{
	_text.setStyle(Text::Underlined);
}

// Text Regular Function
//
// Function sets the style of the text component
// to Regular
void TextComponent::textRegular()
{
	_text.setStyle(Text::Regular);
}

// Get Text Width Function
//
// Function returns the width of the text component
float TextComponent::getTextWidth()
{
	// Obtain width from local bounds of text
	float width = _text.getGlobalBounds().width;

	// Return width
	return width;
}

// Get Text Height Function
//
// Function returns the height of the text component
float TextComponent::getTextHeight()
{
	// Obtain height from local bounds of text
	float height = _text.getGlobalBounds().height;

	// Return height
	return height;
}

// Set Text Origin function
//
// Function sets the origin of the text component
// from a Vector2f as an argument
void TextComponent::setTextOrigin(Vector2f origin)
{
	// Set the origin of the text component
	_text.setOrigin(origin.x, origin.y);
}

// Set Text Origin function
//
// Function invokes previous method to set the 
// origin of the text component, but the function
// accepts two float values (x and y)
void TextComponent::setTextOrigin(float x, float y)
{
	// Invoke the previous method to set the origin
	setTextOrigin(Vector2f(x, y));
}

// Centre the origin
//
// Function determines the width and height of the 
// text component, determines the centre of the 
// text component and sets as the origin
void TextComponent::centreOrigin()
{
	float textWidth = getTextWidth();
	float textHeight = getTextHeight();

	setTextOrigin(textWidth / 2.0f, textHeight / 2.0f);

}


