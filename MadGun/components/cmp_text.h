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
 * TEXT COMPONENT - cmp_text.h
 *
 * Header file for text component
 *
 * Currently populated with boiler plate
 * code from platformer practical
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

		//
		void setFont(string aFont);

		void setPosition(Vector2f position);

		void setCharacterSize(float charSize);

		void setColour(Color colour);

		void setLetterSpacing(float spacing);

		void textBold();

		void textItalic();

		void textUnderlined();

		void textRegular();

		float getTextWidth();

		float getTextHeight();

		void setTextOrigin(Vector2f origin);

		void setTextOrigin(float x, float y);

		void centreOrigin();

	protected:
		// Font shared pointer
		shared_ptr<Font> _font;

		// String
		string _string;

		// Text
		Text _text;
};