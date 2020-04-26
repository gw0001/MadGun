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
 * Date Last Modified: 18/04/2020
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
		static void loadCSVLevelFile(const string&, float tileSize = 100.0f);

		// Unload function
		static void unload();

		// Render Function
		static void Render(RenderWindow &aWindow);

		// Tile type definition
		typedef int Tile;

		// Enumumerator for Unique Tiles
		enum TILES {
			EMPTY = -1, // Empty tile
			START = 63, // Player starting tile
			ENEMY_1 = 106, // Enemy 1 spawn tile
			ENEMY_2 = 107, // Enemy 2 spawn tile
			ENEMY_3 = 108, // Enemy 3 spawn tile
			ENEMY_4 = 109, // Enemy 4 spawn tile
			ENEMY_5 = 110, // Enemy 5 spawn tile
			BOSS = 111, // Boss spawn tile
			PICKUP_LIFE = 112, // Extra Life pickup spawn tile
			PICKUP_HEALTH = 113, // Health pickup spawn tile
			PICKUP_ARMOUR = 114, // Armour pickup spawn tile
			PICKUP_SPECIAL = 115, // Special pick up spawn tile
			PICKUP_WPN_1 = 116, // Weapon 1 pick up spawn tile
			PICKUP_WPN_2 = 117, // Weapon 2 pick up spawn tile
			PICKUP_WPN_3 = 118, // Weapon 3 pick up spawn tile
			PICKUP_AMMO_1 = 119, // Ammo type 1 pick up spawn tile
			PICKUP_AMMO_2 = 120, // Ammo type 2 pick up spawn tile
			PICKUP_AMMO_3 = 121, // Ammo type 3 pick up spawn tile
			HAZARD_1 = 122, // Hazard 1 tile
			HAZARD_2 = 123, // Hazard 2 tile
			HAZARD_3 = 124, // Hazard 3 tile
			DOOR = 125, // Door tile
			WAYPOINT = 126, // Waypoint tile
			EXIT = 127, // Exit tile
		};

		// Get tile at Grid coordinate
		static Tile getTile(Vector2ul);

		//Get the tile at the screenspace position
		static Tile getTileAt(Vector2f);

		// Is on grid function
		static bool isOnGrid(Vector2f);

		// Get Level Width Function
		static size_t getWidth();

		// Get Level Height Function
		static size_t getHeight();

		//Get Screenspace coordinate of tile
		static Vector2f getTilePosition(Vector2ul);

		// Find Tile function
		static vector<Vector2ul> findTiles(Tile t);

		// Find wall tile function
		static vector<Vector2ul> findWallTiles();

		// Get Colour Function
		static Color getColour(Tile t);

		// Set Colour Function
		static void setColour(Tile t, Color c);

		// Set Offset function
		static void setOffset(const Vector2f& _offset);

		// Is Unique Tile funciton
		static bool isUniqueTile(Tile tile);

		// Is Wall Tile function
		static bool isWallTile(Tile tile);

		// Is Waypoint Tile function
		static bool isWaypointTile(Tile tile);

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
		static void buildTexturedSprites();

		// Wall Tile ID vector
		static vector<int> _wallTileIDs;

		// Unique Tile ID vector
		static vector<int> _uniqueTileIDs;

	private:
		// Delete level system constructor
		LevelSystem() = delete;

		// Delete level system destructor
		~LevelSystem() = delete;
};
 