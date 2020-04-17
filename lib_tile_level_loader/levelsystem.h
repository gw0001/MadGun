/*
 * GAMES ENGINEERING - COURSEWORK
 * -------------------------------------
 * MadGun: Gears and Blood
 * -------------------------------------
 * Franceso Fico - 40404272
 * Graeme White - 40415739
 * -------------------------------------
 * Code Author: G. White
 * Date Created: 14/03/2020
 * Date Last Modified: 17/04/2020
 * -------------------------------------
 * LEVEL SYSTEM - levelsystem.h
 *
 * Header file for level system
 *
 */

// Libraries
#pragma once
#include <SFML/Graphics.hpp>
#include <maths.h>
#include <memory>
#include <string>
#include <vector>

// Level system definituon
#define ls LevelSystem

using namespace std; // STD Namespace
using namespace sf; // SFML Namespace

class LevelSystem
{
	public:
		// Load Level File function
		static void loadTXTLevelFile(const string&, float tileSize = 100.0f);
		
		// Load Level File function
		static void loadCSVLevelFile(const string&, float tileSize = 100.0f);

		// Unload function
		static void unload();

		// Render Function
		static void Render(RenderWindow &aWindow);

		// Tile type definition
		typedef int Tile;

		// Enumumerator for Level System
		enum TILES { 
			EMPTY = -1,
			FILLER = 0,
			ENEMY = 1,
			END = 2,
			START = 3,
			WALL = 4,
			WAYPOINT = 5
		};

		// Get tile at Grid coordinate
		static Tile getTile(Vector2ul);

		//Get the tile at the screenspace position
		static Tile getTileAt(Vector2f);

		// Is on grid function
		static bool isOnGrid(sf::Vector2f);

		// Get Level Width Function
		static size_t getWidth();

		// Get Level Height Function
		static size_t getHeight();

		//Get Screenspace coordinate of tile
		static Vector2f getTilePosition(Vector2ul);

		// Find Tile function
		static vector<Vector2ul> findTiles(Tile t);

		// Get Colour Function
		static Color getColour(Tile t);

		// Set Colour Function
		static void setColour(Tile t, Color c);

		// Set Offset function
		static void setOffset(const Vector2f& _offset);

		// Get Offset function
		static const Vector2f& getOffset();

		// Get Tile Size
		static float getTileSize();

	protected:
		// Tile array
		static unique_ptr<Tile[]> _tiles;

		// Level width
		static size_t _width;

		// Level Height
		static size_t _height;

		// Screenspace offset
		static Vector2f _offset;

		// Tile Size
		static float _tileSize;

		// Colour map
		static map<Tile, Color> _colours;

		// Sprites of each tile
		static vector<unique_ptr<RectangleShape>> _sprites;

		// Build Sprites function
		static void buildSprites(bool optimise = true);

		// Build Sprites function
		static void buildTexturedSprites();

	private:
		LevelSystem() = delete;
		~LevelSystem() = delete;
};
 