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
 * TEXT COMPONENT - cmp_text.h
 *
 * Header file for text component
 *
 *
 */

// Libraries
#pragma once
#include <SFML/Graphics/Text.hpp>
#include <ecm.h>

// Namespaces
using namespace std; // Standard namespace
using namespace sf; // SFML namespace

/*
 * TEXT COMPONENT CLASS
 */
class TextComponent : public Component 
{
	public:
		// Blank Text Component constructor (deleted)
		TextComponent() = delete;

		// Text Component constructor
		explicit TextComponent(Entity* p, const string& str = "");

		// Update function
		void update(double dt) override;

		// Render function
		void render() override;

		// Text Component deconstructor
		~TextComponent() override = default;

		// Set Text function
		void setText(const string& str);

		// Set Font function
		void setFont(string aFont);

		// Set Position function
		void setPosition(Vector2f position);		

		// Set Character Size function
		void setCharacterSize(float charSize);

		// Set Colour function
		void setColour(Color colour);

		// Set letter spacing function
		void setLetterSpacing(float spacing);

		// Text Bold function
		void textBold();

		// Text Italic function
		void textItalic();

		// Text Underlined function
		void textUnderlined();

		// Text Regular function
		void textRegular();

	protected:
		// Font shared pointer
		shared_ptr<Font> _font;

		// String
		string _string;

		// Text
		Text _text;
};