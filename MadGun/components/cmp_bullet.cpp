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
 * BULLET COMPONENT- cmp_bullet.cpp
 *
 * Bullet component
 *
 */

// Library
#include "cmp_bullet.h"

// Update function
//
// Function updates the bullet componet
void BulletComponent::update(double dt) 
{
	// Decrement lifetime by time slide
	_lifetime -= dt;

	// Check if lifetime is less than, or equal to, 0
	if (_lifetime <= 0.f) 
	{
		// Set parent of component for deletion
		_parent->setForDelete();
	}
}

// Bullet Component Constructor
BulletComponent::BulletComponent(Entity* p, float lifetime)
	: Component(p), _lifetime(lifetime) {};
