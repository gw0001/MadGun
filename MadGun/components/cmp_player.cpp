/*
 * GAMES ENGINEERING - COURSEWORK
 * -------------------------------------
 * MadGun: Gears and Blood
 * -------------------------------------
 * Franceso Fico - 40404272
 * Graeme White - 40415739
 * -------------------------------------
 * Code Author: G. White
 * Date Created: 24/04/2020
 * Date Last Modified: 24/04/2020
 * -------------------------------------
 * PLAYER COMPONENT - cmp_player.cpp
 *
 * Player Component class
 *
 */

 // Libraries
#include "cmp_player.h"

// Components


// Enemy Stats Component constructor
PlayerStatsComponent::PlayerStatsComponent(Entity* p) : Component(p)
{
	resetStats();
};

// Set Health Function
//
// Function sets the health of the player
void PlayerStatsComponent::setHealth(int healthValue)
{
	// Set health to the value from the argument
	_health = healthValue;
}

// Reduce Health Function
//
// Function reduces the players health
void PlayerStatsComponent::reduceHealth(int reductionVal)
{
	// Reduce health by the value from the argument
	_health -= reductionVal;
}

// Get Health function
//
// Function returns the health value of the player
int PlayerStatsComponent::getHealth()
{
	// Return the health value
	return _health;
}

// Get Direction Function
//
// Returns the direction of the player
int PlayerStatsComponent::getDirection()
{
	// Return the direction of the player
	return _direction;
}

// Invert Direction Function
//
// Inverts the players direction
void PlayerStatsComponent::invertDirection()
{
	// Invert the direction of the player
	_direction = -_direction;
}

// Increment Score function
//
// Function used to increase the players score by a value
void PlayerStatsComponent::increaseScore(int scoreAddition)
{
	// Add value from argument to the Score
	_score += scoreAddition;
}

// Add Life function
//
// Funtion adds a life to the players lives stock
void PlayerStatsComponent::addLife()
{
	// Increment the lives by 1
	_lives++;
}

// Get Lives function
//
// Function returns the value held by the players lives variable
int PlayerStatsComponent::getLives()
{
	return _lives;
}

// Lose Life function
//
// Funtion removes a life to the players lives stock
void PlayerStatsComponent::loseLife()
{
	_lives -= 1;
}

// Reset stats function
//
// Function resets stats to default values
void PlayerStatsComponent::resetStats()
{
	// Set player to the maximum health
	_health = _maxHealth;

	// Give player the default amount of lives
	_lives = _defaultLives;

	// Start player with a default starting score
	_score = _defaultScore;

	// Set facing left boolean to false
	_facingLeft = false;

	// Set facing right boolean to true
	_facingRight = true;
}

// Is Facing Left function
//
// Returns the value of the facing left variable
bool PlayerStatsComponent::isFacingLeft()
{
	// Return the value of the facing left variable
	return _facingLeft;
}

// Is Facing Right function
//
// Returns the value of the facing right variable
bool PlayerStatsComponent::isFacingRight()
{
	// return the value of the facing right variable
	return _facingRight;
}

// Set Facing Left function
void PlayerStatsComponent::setFacingLeft(bool leftValue)
{
	// Set facing left value
	_facingLeft = leftValue;
}

//Set Facing Right function
void PlayerStatsComponent::setFacingRight(bool rightValue)
{
	// Set facing right value
	_facingRight = rightValue;
}