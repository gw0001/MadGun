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
 * Date Last Modified: 26/04/2020
 * -------------------------------------
 * SPRITE COMPONENT
 * - cmp_sprite.h
 *
 * Header file for sprite component
 *
 * Currently populated with boiler plate
 * code from platformer practical
 *
 */

// Libraries
#pragma once
#include "ecm.h"
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>

// Namespaces
using namespace std; // Standard namespace
using namespace sf; // SFML namespace

/*
 * SPRITE COMPONENT CLASS
 */
class SpriteComponent : public Component 
{
	protected:
		// Sprite Shared Pointer
		shared_ptr<Sprite> _sprite;

		// Texture Shared Pointer
		shared_ptr<Texture> _texture;

	public:
		// Blank Sprite Component constructor (deleted)
		SpriteComponent() = delete;

		// Sprite Component constructor
		explicit SpriteComponent(Entity* p);

		// Update function
		void update(double dt) override;

		// Render function
		void render() override;

		// Get Sprite function
		Sprite& getSprite() const;

		// Set Texture function
		void setTexure(shared_ptr<Texture> tex);
};

/*
 * SHAPE COMPONENT CLASS
 */
class ShapeComponent : public Component 
{
	protected:
		// Shape pointer
		shared_ptr<Shape> _shape;

	public:
		// Blank Shape Component constructor (deleted)
		ShapeComponent() = delete;

		// Shape Component constructor
		explicit ShapeComponent(Entity* p);

		// Update function
		void update(double dt) override;

		// Render function
		void render() override;

		// Get Shape function
		Shape& getShape() const;

		// Set Shape Function
		template <typename T, typename... Targs> void setShape(Targs... params) 
		{
			// Reset shape
			_shape.reset(new T(params...));
		}
};

/*
 * PLAYER SPRITE COMPONENT
 */

class PlayerSpriteComponent : public Component
{
	protected:
		// Sprite Shared Pointer
		shared_ptr<Sprite> _playerSprite;

		// Left Facing Texture Shared Pointer
		shared_ptr<Texture> _leftFacingTexture;

		// Right Facing Texture Shared Pointer
		shared_ptr<Texture> _rightFacingTexture;

	public:
		// Blank Sprite Component constructor (deleted)
		PlayerSpriteComponent() = delete;

		// Sprite Component constructor
		explicit PlayerSpriteComponent(Entity* p);

		// Update function
		void update(double dt) override;

		// Render function
		void render() override;

		// Get Sprite function
		Sprite& getSprite() const;

		// Set Left Facing Texture function
		void setLeftFacingTexure(shared_ptr<Texture> tex);

		// Set Right Facing Texture
		void setRightFacingTexure(shared_ptr<Texture> tex);

		// Set Sprite to face Left
		void spriteFaceLeft();

		// Sprite Face Right function
		void spriteFaceRight();
};