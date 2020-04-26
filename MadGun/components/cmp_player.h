/*
 * GAMES ENGINEERING - COURSEWORK
 * -------------------------------------
 * MadGun: Gears and Blood
 * -------------------------------------
 * Franceso Fico - 40404272
 * Graeme White - 40415739
 * -------------------------------------
 * Code Author: G. White
 * Date Created: 25/04/2020
 * Date Last Modified: 25/04/2020
 * -------------------------------------
 * PLAYER COMPONENT - cmp_player.h
 *
 * Header file for player component
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

class PlayerStatsComponent : public Component
{
	private:
		// Health
		int _health;

		// Direction
		int _direction;

		// Points
		int _score;

		// Lives
		int _lives;

		// Max Health
		int _maxHealth = 100;

		// Max Lives
		int _maxLives = 10;

		// Starting Score
		int _defaultScore = 0;

		// Default Lives
		int _defaultLives = 3;

		// Facing Left
		bool _facingLeft;

		// Facing Right
		bool _facingRight;

	public:
		// Delete standard constructor
		PlayerStatsComponent() = delete;

		// Enemy Stats Component constructor
		explicit PlayerStatsComponent(Entity* p);

		// Set Health function
		void setHealth(int healthValue);

		// Reduce Health
		void reduceHealth(int reductionVal);

		// Get Health function
		int getHealth();

		// Get Direction Function
		int getDirection();

		// Invert Direction Function
		void invertDirection();

		// Increment Score function
		void increaseScore(int scoreAddition);

		// Add Life function
		void addLife();

		// Get Lives function
		int getLives();

		// Lose Life function
		void loseLife();

		// Reset stats function
		void resetStats();

		// Is Facing Left function
		bool isFacingLeft();

		// Is Facing Right function
		bool isFacingRight();

		// Set Facing Left function
		void setFacingLeft(bool leftValue);

		//Set Facing Right function
		void setFacingRight(bool rightValue);
};