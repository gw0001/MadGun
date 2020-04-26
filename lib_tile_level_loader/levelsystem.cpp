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
 * LEVEL SYSTEM - levelsystem.cpp
 *
 * Level system
 *
 */

// Libraries
#include "LevelSystem.h"
#include <iostream>
#include <sstream>
#include <fstream>

// Name spaces
using namespace std; // Standard Namespace
using namespace sf; // SFML Namespace

// Sprite Sheet texture
Texture spriteSheet;

// Tile set sprite width
int tsSpriteWidth = 32;

// Tile set sprite height
int tsSpriteHeight = 32;

// Colour Map
map<LevelSystem::Tile, Color> LevelSystem::_colours
{
	// White wall
	{4, Color::White},

	// Red end
	{EXIT, Color::Red} 
};

// Wall Tile ID vector
//
// Vector is populated with the IDs of wall tiles
vector<int> LevelSystem::_wallTileIDs = {
	 0, 1, 2, 3, 4, 5, 6, 7,
	 8, 9,10,11,12,13,14,15,
	16,17,18,19,20,21,22,23,
	24,25,26,27,28,29,30,31,
	32,33,34,35,36,37,38,39,
	40,41,42,43,44,45,46,47,
	48,49,50,51,52,53,54,55,
	56,57,58,59,60,61,62,
	64,65,66,67,68,69,70,71
};


// Unique Tile ID vector
//
// Vector is populated with tiles with unique
// tile IDs (e.g, spawn points, empty tiles, etc)
vector<int> LevelSystem::_uniqueTileIDs = {
	 -1,  63, 106, 107, 108, 109,
	110, 111, 112, 113, 114, 115,
	116, 117, 118, 119, 120, 121, 
	122, 123, 124, 125, 126, 127
};

// Get colour function
//
// Function returns the colour of a tile
Color LevelSystem::getColour(LevelSystem::Tile t) 
{
	// Find colour of tile
	auto it = _colours.find(t);

	// Check if colour is at the end
	if (it == _colours.end()) 
	{
		// Set colour to transparent
		_colours[t] = Color::Transparent;
	}

	// Return colours
	return _colours[t];
}

// Set colour function
//
// Function sets colour of the tile
void LevelSystem::setColour(LevelSystem::Tile t, Color c) 
{
	// Set colour of tile
	_colours[t] = c;
}

// Unique Tile pointer
unique_ptr<LevelSystem::Tile[]> LevelSystem::_tiles;

// Tile Width
size_t LevelSystem::_width;

// Tile Height
size_t LevelSystem::_height;

// Tile size
float LevelSystem::_tileSize(100.f);

// Tile offset 
Vector2f LevelSystem::_offset(0.0f, 0.0f);

// Sprite vector
vector<unique_ptr<RectangleShape>> LevelSystem::_sprites;

// Load CSV level file
//
// Function loads level from a CSV file. As this is a CSV file
// file contains values seperated by commas. Function reads the
// values and ignores the commas
void LevelSystem::loadCSVLevelFile(const string& path, float tileSize)
{
	// Set tile size
	_tileSize = tileSize;

	// Temporary width and height
	size_t w = 0, h = 0;

	// String buffer for CSV file
	string bufferString;

	// Temporary tile vector
	vector<int> temp_tiles;

	// Load in file to buffer
	ifstream CSVfile(path);

	// Check path exists
	if (CSVfile.good())
	{
		// Loop whilst reading each line of CSV file
		while (getline(CSVfile, bufferString))
		{
			// New String Stream
			stringstream stringStream(bufferString);

			// Variable of type integer for storing the values from the string stream
			int intValue;

			// Loop whilst copying integer values from string stream
			while (stringStream >> intValue)
			{
				// Add value to temporary tile vector
				temp_tiles.push_back(intValue);

				// Check if next value is a comma
				if (stringStream.peek() == ',')
				{
					// Comma found, ignore it
					stringStream.ignore();
				}
			}

			// After line has been read, check the value of the level width
			if (w == 0)
			{
				// Width is 0, set width to the current size of the buffer vector
				w = temp_tiles.size();
			}

			// Increment the level height by 1
			h++;
		}
	}
	// Path doesn't exist
	else
	{
		// Throw error message and include path
		throw string("Couldn't open level file: ") + path;
	}

	// Output level width to the console
	cout << "Level Width: " << w << endl;

	// Output level height to the console
	cout << "Level Height: " << h << endl;

	// Check if size of buffer vector matches the value of the level width by the level height
	if (temp_tiles.size() != (w * h))
	{
		// Size doesn't match, throw error message and include path
		throw string("Can't parse level file") + path;
	}

	// Set tile vector to size of the level width by the level height
	_tiles = make_unique<Tile[]>(w * h);

	// Set width of level
	_width = w;

	// Set height of level
	_height = h;

	// Copy tiles in temporary tile vector to main tile vector
	copy(temp_tiles.begin(), temp_tiles.end(), &_tiles[0]);

	// Display success message to the console
	cout << "Level " << path << " Loaded. " << w << "x" << h << std::endl;

	// Close CSV file
	CSVfile.close();

	// Build sprites with textures
	buildTexturedSprites();
}

// Build Textured Sprites
//
// Function for building tile sprites and applying
// textures from sprite sheet, depending on the tile's
// ID
void LevelSystem::buildTexturedSprites()
{
	// Clear Sprite vector
	_sprites.clear();

	// Load world sprite sheet and determine if file path is good
	if (!spriteSheet.loadFromFile("res/img/worldTiles.png"))
	{
		// Cannot load from file, throw error message
		throw string("Cannot load sprite sheet! Check the file path!");
	}

	// Determine the width of the sprite sheet texture
	int textureWidth = spriteSheet.getSize().x;

	// Determine the height of the textyre
	int textureHeight = spriteSheet.getSize().y;

	// Determine the number of tiles in X direction
	int tilesInX = textureWidth / tsSpriteWidth;

	// Determine the number of tiles in the Y direction
	int tilesInY = textureHeight / tsSpriteHeight;

	// Iterate over all tile y-coordinates
	for (int y = 0; y < _height; y++)
	{
		// Iterate over all tile x-coordinates
		for (int x = 0; x < _width; x++)
		{
			// Create unique rectangle shape sprite
			auto sprite = make_unique<RectangleShape>();

			// Tile Position Vector as Maths Vector2ul
			Vector2ul tilePos = Vector2ul(x, y);

			// Tile from CSV file at X and Y
			Tile CSVtile = getTile(tilePos);

			// Set the tile position of the sprite
			sprite->setPosition(getTilePosition(tilePos));	

			// Check that tile is not considered a unique tile to avoid adding textures to these tiles
			if (isUniqueTile(CSVtile) == false)
			{
				// Set texture of the sprite to the sprite sheet
				sprite->setTexture(&spriteSheet);

				// Tile ID
				int tileID = 0;

				// Iterate over all texture squares in Y
				for (int tex_Y = 0; tex_Y < tilesInY; tex_Y++)
				{
					// Iterate over all texture squares in X
					for (int tex_X = 0; tex_X < tilesInX; tex_X++)
					{
						// Check if the value of the CSVtile matches the tile ID
						if (CSVtile == tileID)
						{
							// ID's match
							// Determine the X Coordinate of the texture
							int texCoord_X = (tex_X * tsSpriteWidth);

							// Determine the Y Coordinate of the texture
							int texCoord_Y = (tex_Y * tsSpriteHeight);

							// Set the sprites texture to the coordinates determined and the width and height of the texture
							sprite->setTextureRect(IntRect(texCoord_X, texCoord_Y, tsSpriteWidth, tsSpriteHeight));
						}
						// Increment texture ID
						tileID++;
					}
				}
				// Set texture size of sprite
				sprite->setSize(Vector2f(_tileSize, _tileSize));
			}
			// Add sprite to the sprites vector
			_sprites.push_back(move(sprite));
		}
	}
}

// Render function
//
// Function for rendering tiles to window
void LevelSystem::Render(RenderWindow& window)
{
	// Iterate over all sprites
	for (auto& t : _sprites) 
	{
		// Draw sprite to window
		window.draw(*t);
	}
}

// Get Tile Function
//
// Function returns the tile as a Vector2ul
LevelSystem::Tile LevelSystem::getTile(Vector2ul p) 
{
	// Check tile coordinates does not exceed width or height of level
	if (p.x > _width || p.y > _height) 
	{
		// Tile exceeds limits, throw error message to console
		throw string("Tile out of range: ") + to_string(p.x) + "," + to_string(p.y) + ")";
	}

	// Return specific tile
	return _tiles[(p.y * _width) + p.x];
}

// Get Width function
//
// Returns the tile width
size_t LevelSystem::getWidth()
{ 
	// Return level width
	return _width;
}

// Get Tile Height
//
// Function returns the tile height
size_t LevelSystem::getHeight()
{
	// Return level height
	return _height; 
}

// Get Tile Position
//
// Obtains the tile position as a Vector2f
Vector2f LevelSystem::getTilePosition(Vector2ul p) 
{
	// Return tile position as a Vector2f
	return (Vector2f(p.x, p.y) * _tileSize) + _offset;
}

// Find Tiles function
//
// Function returns specific tiles
vector<Vector2ul> LevelSystem::findTiles(LevelSystem::Tile type) 
{
	// Create an empty vector
	auto v = vector<Vector2ul>();
	
	// Iterate over all tiles in level
	for (size_t i = 0; i < _width * _height; ++i) 
	{
		// Check if tile in tiles vector matches the type required
		if (_tiles[i] == type) 
		{
			// Add tile to vector
			v.push_back({ i % _width, i / _width });
		}
	}

	// Return vector
	return v;
}

// Find Wall Tiles function
//
// Function returns vector of wall tiles
vector<Vector2ul> LevelSystem::findWallTiles() 
{
	// Create empty vector
	auto v = vector<Vector2ul>();

	// Iterate over all tiles in level
	for (size_t i = 0; i < _width * _height; ++i)
	{
		// Iterate over all specified wall tiles
		for (int j = 0; j < _wallTileIDs.size(); j++)
		{
			// Check if tile in tiles vector matches the ID of a known wall tile
			if (_tiles[i] == _wallTileIDs[j])
			{
				// Wall tile found, add it to the vector
				v.push_back({ i % _width, i / _width });
			}
		}
	}

	// Return vector
	return v;
}

//Is Unique Tile funciton
//
//Method checks if a tiles ID is considered a unique ID
bool LevelSystem::isUniqueTile(Tile tile)
{
	// Check boolean set to false
	bool check = false;

	// Iterate over all values held in unique tile ID vector
	for (int i = 0; i < _uniqueTileIDs.size(); i++)
	{
		// Check if tile matches that of any of the unique IDs
		if (tile == _uniqueTileIDs[i])
		{
			// Unique ID found, set check to true
			check = true;

			// Break loop
			break;
		}
	}

	// Return check boolean
	return check;
}

//Is Wall Tile funciton
//
//Method checks if a tiles ID is considered a unique ID
bool LevelSystem::isWallTile(Tile tile)
{
	// Check boolean set to false
	bool check = false;

	// Iterate over all values held in unique tile ID vector
	for (int i = 0; i < _wallTileIDs.size(); i++)
	{
		// Check if tile matches that of any of the unique IDs
		if (tile == _wallTileIDs[i])
		{
			// Unique ID found, set check to true
			check = true;

			// Break loop
			break;
		}
	}

	// Return check boolean
	return check;
}

//Is Waypoint Tile funciton
//
//Method checks if a tiles ID is considered a unique ID
bool LevelSystem::isWaypointTile(Tile tile)
{
	// Check boolean set to false
	bool check = false;

	// Check if tile matches that of any of the unique IDs
	if (tile == ls::WAYPOINT)
	{
		// Unique ID found, set check to true
		check = true;
	}

	// Return check boolean
	return check;
}

// Get Tile At function
//
// Function returns the tile at a specific location
LevelSystem::Tile LevelSystem::getTileAt(Vector2f v) 
{
	// Remove offset from tile coordinates
	auto a = v - _offset;

	// Check tile is within range
	if (a.x < 0 || a.y < 0) 
	{
		throw string("Tile out of range ");
	}

	// Return tile found at coordinates
	return getTile(Vector2ul((v - _offset) / (_tileSize)));
}

// Is On Grid function
//
// Function determines if the tile is on the grid
bool LevelSystem::isOnGrid(Vector2f v) 
{
	// Remove offset from tile coordinates
	auto a = v - _offset;

	// Check tile is within range
	if (a.x < 0 || a.y < 0) 
	{
		// Tile outwidth range, return false
		return false;
	}

	// Change tile coordinates to Vector2ul
	auto p = Vector2ul((v - _offset) / (_tileSize));

	// Check tile is within width or height of the level
	if (p.x > _width || p.y > _height) 
	{
		// Tile is not within width or height, return false
		return false;
	}

	// Return true
	return true;
}

// Set Offset function
//
// Function sets the offset for the tiles
void LevelSystem::setOffset(const Vector2f& _offset) 
{
	// Set offset
	LevelSystem::_offset = _offset;

	// Build sprites
	buildTexturedSprites();
}

// Unload function
//
// Function unloads the tiles
void LevelSystem::unload() 
{
	// Send message to console
	cout << "LevelSystem unloading\n";

	// Clear sprites
	_sprites.clear();

	// Reset tiles
	_tiles.reset();

	// Set width to 0
	_width = 0;

	// Set height to 0
	_height = 0;

	// Set offset to 0, 0
	_offset = { 0, 0 };
}

// Get Offset function
//
// Function returns the offset of the tiles
const Vector2f& LevelSystem::getOffset() 
{ 
	// Return tile offset
	return _offset; 
}

// Get Tile Size function
//
// Function returns the size of the tiles
float LevelSystem::getTileSize() 
{ 
	// Return tile size
	return _tileSize; 
}