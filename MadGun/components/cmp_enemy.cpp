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
 * ENEMY COMPONENT - cmp_enemy.cpp
 *
 * Enemy Component class
 *
 */

 // Libraries
#include "cmp_enemy.h"

// Enemy Stat Compononet constructor
EnemyStatsComponent::EnemyStatsComponent(Entity* p, int type) : Component(p)
{
	// If type = 1
	if (type == 1)
	{
		// Set health to 10
		_health = 3;
		_viewDistance = 10.0f;
		_points = 10;
	}
	// If type 2
	else if (type == 2)
	{
		// Set health to 2
		_health = 20;
		_viewDistance = 10.0f;
		_points = 30;
	}
	// If type 3
	else if (type == 3)
	{
		_health = 50;
		_viewDistance = 25.0f;
		_points = 70;
	}
	else if (type == 4)
	{
		_health = 75;
		_viewDistance = 25.0f;
		_points = 100;
	}
	else
	{
		_health = 100;
		_viewDistance = 50.0f;
		_points = 200;
	}
	_direction = 1;
};

// Set Health value function
//
// Function sets the health of the enemy stat
void EnemyStatsComponent::setHealth(int healthValue)
{
	_health = healthValue;
}

// Reduce Health Function
//
// Function reduces health of the enemy
void EnemyStatsComponent::reduceHealth(int reductionVal)
{
	_health -= reductionVal;
}

// Get Health function
//
// Returns the health of the Enemy
int EnemyStatsComponent::getHealth()
{
	return _health;
}

// Get Direction function
//
// Function returns the direction of the enemy
int EnemyStatsComponent::getDirection()
{
	return _direction;
}

// Invert Direction function
//
// Function inverts the direction of the enemy
void EnemyStatsComponent::invertDirection()
{
	_direction = -_direction;
}

// Get View Distance function
//
// Function returns the view distance of the 
float EnemyStatsComponent::getViewDistance()
{
	return _viewDistance;
}

