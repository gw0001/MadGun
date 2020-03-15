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
 * ACTOR MOVEMENT COMPONET
 * - cmp_actor_movement.cpp
 *
 * Actor movement component
 *
 */

// Library
#include "cmp_actor_movement.h"
#include <LevelSystem.h>
#include <engine.h>
#include <iostream>

// Update function
//
// Function updates the actor movement component
void ActorMovementComponent::update(double dt) 
{
}

// Actor Movement Component Constructor
//
// When constructed, initialises the actor movment component
// with a speed of 100.0f and ties to a parent entity
ActorMovementComponent::ActorMovementComponent(Entity* p)
	: _speed(100.0f), Component(p) {};

// Valid Move
//
// Function determines if the actor has made a valid move
bool ActorMovementComponent::validMove(const Vector2f& pos) 
{
	// Return true if actor's position isn't a wall
	return (LevelSystem::getTileAt(pos) != LevelSystem::WALL);
}

// Move function
//
// Function allows actor movement component to move
void ActorMovementComponent::move(const Vector2f& p) 
{
	// Obtain new position of component
	auto pp = _parent->getPosition() + p;
	
	// Check if a position is a valid move
	if (validMove(pp)) 
	{
		// Set player position to new position
		_parent->setPosition(pp);
	}
}

// Move function
//
// Overloaded version of move function
void ActorMovementComponent::move(float x, float y) 
{
	// Invoke previous move function
	move(Vector2f(x, y));
}
