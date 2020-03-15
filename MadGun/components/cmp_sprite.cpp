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
 * SPRITE COMPONENT
 * - cmp_sprite.cpp
 *
 * Sprite component
 *
 * Currently populated with boiler plate
 * code from platformer practical
 *
 */

 // Libraries
#include "cmp_sprite.h"
#include "system_renderer.h"

// Set Texture function
//
// Function sets the texture of the sprite component
void SpriteComponent::setTexure(shared_ptr<Texture> tex)
{
	// Set texture
	_texture = tex;

	// Set texture of sprite
	_sprite->setTexture(*_texture);
}

// Sprite Component constructor
SpriteComponent::SpriteComponent(Entity* p)
    : Component(p), _sprite(make_shared<Sprite>()) {}

// Update function
//
// Function updates the sprite component
void SpriteComponent::update(double dt) 
{
	// Set position
	_sprite->setPosition(_parent->getPosition());

	// Set rotation
	_sprite->setRotation(_parent->getRotation());
}

// Render function
//
// Function renders the sprite component
void SpriteComponent::render() 
{
	// Add sprite component to the renderer queue
	Renderer::queue(_sprite.get()); 
}

// Update function
//
// Function updates the shape component
void ShapeComponent::update(double dt) 
{
	// Set position
	_shape->setPosition(_parent->getPosition());

	// Set rotation
	_shape->setRotation(_parent->getRotation());
}

// Render function
//
// Function renders the shape component
void ShapeComponent::render() 
{
	// Add shape component to the renderer queue
	Renderer::queue(_shape.get()); 
}

// Get Shape
//
// Function obtains the shape
Shape& ShapeComponent::getShape() const 
{
	return *_shape; 
}

// Shape Component constructor
ShapeComponent::ShapeComponent(Entity* p)
    : Component(p), _shape(make_shared<CircleShape>()) {}

// Get Sprite
//
// Function returns the sprite
Sprite& SpriteComponent::getSprite() const
{
	return *_sprite; 
}
