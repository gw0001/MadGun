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
 * ENEMY AI COMPONENT- cmp_enemy_ai.cpp
 *
 * Enemy AI component
 *
 * Currently populated with boiler plate
 * code from platformer practical
 *
 */

// Library
#include "cmp_enemy_ai.h"
#include "cmp_sprite.h"

// Update function
//
// Updates the Enemy AI Component
void EnemyAIComponent::update(double dt) 
{
	// Movement amount
	auto mov = _direction * (float)(dt * _speed);
	
	// Increment enemy movement in x axis
	mov.x += _direction.x * 16.f;
	
	// Check if invalid move made
	if (!enemyValidMove(_parent->getPosition() + mov)) 
	{
		// Inverse the direction
		_direction *= -1.f;

		// Obtain shape from the parent
		auto shape = _parent->get_components<SpriteComponent>();

		// Obtain the scale of the parent's sprite
		auto spriteScale = shape[0]->getSprite().getScale();

		// Inverse the x value to alter the direction that the sprite is facing
		shape[0]->getSprite().setScale(Vector2f(spriteScale.x * -1.0, 1.0));
	}

	// Move component
	move(_direction * (float)(dt * _speed));

	// Update Actor Movement Component
	ActorMovementComponent::update(dt);
}

// Enemy AI Component Constructor
EnemyAIComponent::EnemyAIComponent(Entity* p) : ActorMovementComponent(p) 
{
	// Set direction
	_direction = Vector2f(1.0f, 0);

	// Set speed
	_speed = 100.0f;
}

// Set Speed
//
// Function that allows the speed of the component to be set
void EnemyAIComponent::setSpeed(float speedVal)
{
	_speed = speedVal;
}