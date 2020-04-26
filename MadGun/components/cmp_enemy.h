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
 * Date Last Modified: 25/04/2020
 * -------------------------------------
 * ENEMY COMPONENT - cmp_enemy.h
 *
 * Header file for enemy component
 *
 */

// Libraries
#pragma once
#include <ecm.h>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>

// Namespaces
using namespace std; // Standard namespace
using namespace sf; // SFML namespace

class EnemyStatsComponent : public Component
{
	private:
		// Health
		int _health;

		// Direction
		int _direction;

		// View Length
		float _viewDistance;

		// Points
		int _points;
		
	public:
		// Delete standard constructor
		EnemyStatsComponent() = delete;

		// Enemy Stats Component constructor
		explicit EnemyStatsComponent(Entity* p, int _type);

		// Set Health function
		void setHealth(int healthValue);

		// Reduce health function
		void reduceHealth(int reductionVal);

		// Get Health function
		int getHealth();

		// Get Direction Function
		int getDirection();

		// Invert Direction Function
		void invertDirection();

		// Get View Distance Function
		float getViewDistance();

};