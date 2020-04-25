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
 * ENEMY
 * - ecm.h
 *
 * Header file for entity component
 * manager
 *
 */

 // Libraries
#include "cmp_enemy.h"

// Components
EnemyStatsComponent::EnemyStatsComponent(Entity* p, int type) : Component(p)
{
	// If type = 1
	if (type == 1)
	{
		_health = 50;
		_viewDistance = 10.0f;
		_points = 10;
	}
	else if (type == 2)
	{
		_health = 100;
		_viewDistance = 10.0f;
		_points = 30;
	}
	else if (type == 3)
	{
		_health = 150;
		_viewDistance = 25.0f;
		_points = 70;
	}
	else if (type == 4)
	{
		_health = 200;
		_viewDistance = 25.0f;
		_points = 100;
	}
	else
	{
		_health = 300;
		_viewDistance = 50.0f;
		_points = 200;
	}
	_direction = 1;
};

void EnemyStatsComponent::setHealth(int healthValue)
{
	_health = healthValue;
}

void EnemyStatsComponent::reduceHealth(int reductionVal)
{
	_health -= reductionVal;
}

void EnemyStatsComponent::damageEnemy(int damageValue)
{
	reduceHealth(damageValue);
}

int EnemyStatsComponent::getHealth()
{
	return _health;
}

int EnemyStatsComponent::getDirection()
{
	return _direction;
}

void EnemyStatsComponent::invertDirection()
{
	_direction = -_direction;
}

float EnemyStatsComponent::getViewDistance()
{
	return _viewDistance;
}

