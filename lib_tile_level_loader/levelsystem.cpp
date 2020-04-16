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
 * Date Last Modified: 15/03/2020
 * -------------------------------------
 * LEVEL SYSTEM - levelsystem.cpp
 *
 * Level system
 *
 */

// Libraries
#include "LevelSystem.h"
#include <fstream>

// Name spaces
using namespace std;
using namespace sf;

// Colour Map
map<LevelSystem::Tile, Color> LevelSystem::_colours
{
	// White wall
	{WALL, Color::White},
	// Red end
	{END, Color::Red} 
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
Vector2f LevelSystem::_offset(0.0f, 30.0f);

// Sprite vector
vector<unique_ptr<RectangleShape>> LevelSystem::_sprites;

// Load level file
void LevelSystem::loadTXTLevelFile(const string& path, float tileSize) 
{
	// Set tile size
	_tileSize = tileSize;

	// Temporary width and height
	size_t w = 0, h = 0;

	// String buffer for text file
	string buffer;

	// Load in file to buffer
	ifstream f(path);

	// Check path exists
	if (f.good()) 
	{
		// Move position to end of the file
		f.seekg(0, std::ios::end);

		// Resize buffer string
		buffer.resize(f.tellg());

		// Move position to the start of the file
		f.seekg(0);

		// Read
		f.read(&buffer[0], buffer.size());

		// Close
		f.close();
	}
	// Path doesn't exist
	else 
	{
		// Throw error message and incluide path
		throw string("Couldn't open level file: ") + path;
	}

	// Temporary tile vector
	std::vector<Tile> temp_tiles;

	// Width check 
	int widthCheck = 0;

	// Iterate over all characters in the buffer
	for (int i = 0; i < buffer.size(); ++i)
	{
		// Obtain character at position i
		const char c = buffer[i];

		// If line contains null
		if (c == '\0') 
		{ 
			// Break
			break; 
		}

		// If line contains null
		if (c == ',')
		{
			// Break
			i++;
		}

		//Check if at new line
		if (c == '\n') 
		{ 
			// Check if width has been written
			if (w == 0) 
			{  
				// Set width
				w = i;
			}
			// Else, check if width is non-uniform
			else if (w != (widthCheck - 1)) 
			{
				throw string("non uniform width:" + to_string(h) + " ") + path;
			}
			// Set width check to 0
			widthCheck = 0;

			// increment the height
			h++;
		}
		else 
		{
			// Add tile to temporary tile vector
			temp_tiles.push_back((Tile)c);
		}

		// Increment width check
		++widthCheck;
	}

	// Check if size of temporary vector matches width by height
	if (temp_tiles.size() != (w * h)) 
	{
		// Size doesn't match, throw error message and include path
		throw string("Can't parse level file") + path;
	}

	// Set tile vector to size of width times height
	_tiles = std::make_unique<Tile[]>(w * h);

	// Set width
	_width = w;

	// Set height
	_height = h;

	// Copy tiles in temporary tile vector to main tile vector
	copy(temp_tiles.begin(), temp_tiles.end(), &_tiles[0]);

	// Display success message to the console
	cout << "Level " << path << " Loaded. " << w << "x" << h << std::endl;

	// Build sprites
	buildSprites();
}

// Load CSV level file
//
// Function loads level from a CSV file. Similar to previous
// function, but method removes commas that separate values 
void LevelSystem::loadCSVLevelFile(const string& path, float tileSize)
{
	// Set tile size
	_tileSize = tileSize;

	// Temporary width and height
	size_t w = 0, h = 0;

	// String buffer for CSV file
	string buffer;

	// Load in file to buffer
	ifstream f(path);

	// Check path exists
	if (f.good())
	{
		// Move position to end of the file
		f.seekg(0, std::ios::end);

		// Resize buffer string
		buffer.resize(f.tellg());

		// Move position to the start of the file
		f.seekg(0);

		// Read
		f.read(&buffer[0], buffer.size());

		// Close
		f.close();
	}
	// Path doesn't exist
	else
	{
		// Throw error message and incluide path
		throw string("Couldn't open level file: ") + path;
	}

	// Iterate over all characters from the file buffer string
	for (int i = 0; i < buffer.size(); i++)
	{
		// Check if character at position i in string is a comma
		if (buffer[i] == ',')
		{
			// Comma found, remove it from the buffer string
			buffer.erase(buffer.begin() + i);

			// Decrement i
			i--;
		}
	}

	// Temporary tile vector
	std::vector<Tile> temp_tiles;

	// Width check 
	int widthCheck = 0;

	// Iterate over all characters in the buffer
	for (int i = 0; i < buffer.size(); ++i)
	{
		// Obtain character at position i
		const char c = buffer[i];

		// If line contains null
		if (c == '\0')
		{
			// Break
			break;
		}

		//Check if at new line
		if (c == '\n')
		{
			// Check if width has been written
			if (w == 0)
			{
				// Set width
				w = i;
			}
			// Else, check if width is non-uniform
			else if (w != (widthCheck - 1))
			{
				throw string("non uniform width:" + to_string(h) + " ") + path;
			}
			// Set width check to 0
			widthCheck = 0;

			// increment the height
			h++;
		}
		else
		{
			// Add tile to temporary tile vector
			temp_tiles.push_back((Tile)c);
		}

		// Increment width check
		++widthCheck;
	}

	// Check if size of temporary vector matches width by height
	if (temp_tiles.size() != (w * h))
	{
		// Size doesn't match, throw error message and include path
		throw string("Can't parse level file") + path;
	}

	// Set tile vector to size of width times height
	_tiles = std::make_unique<Tile[]>(w * h);

	// Set width
	_width = w;

	// Set height
	_height = h;

	// Copy tiles in temporary tile vector to main tile vector
	copy(temp_tiles.begin(), temp_tiles.end(), &_tiles[0]);

	// Display success message to the console
	cout << "Level " << path << " Loaded. " << w << "x" << h << std::endl;

	// Build sprites
	buildSprites();
}

void LevelSystem::buildSprites(bool optimise) 
{
	// Clear sprite vector
	_sprites.clear();

	// TP struct
	struct tp 
	{
		// Positon
		sf::Vector2f p;

		// Scale
		sf::Vector2f s;

		// Colour
		sf::Color c;
	};

	// TPS vector
	vector<tp> tps;

	// Tile scale
	const auto tls = Vector2f(_tileSize, _tileSize);

	// Iterate over all y
	for (size_t y = 0; y < _height; ++y)
	{
		// Iterate over x
		for (size_t x = 0; x < _width; ++x)
		{
			// Get tile at position x, y
			Tile t = getTile({ x, y });
			
			// Check if tile is empty
			if (t == EMPTY) 
			{
				// Contine
				continue;
			}

			// Add tile to TPS vector
			tps.push_back({ getTilePosition({x, y}), tls, getColour(t) });
		}
	}

	// Obtain size of Tile Positions vector
	const auto nonempty = tps.size();

	// If tile of the same type are next to each other,
	// We can use one large sprite instead of two.
	
	// Check if optimise is true and TPS vector is not empty
	if (optimise && nonempty) 
	{
		// Optimised tile vector
		vector<tp> tpo;

		// Last TP
		tp last = tps[0];

		// Set same count to 0
		size_t samecount = 0;

		// iterate over all non-empty tiles
		for (size_t i = 1; i < nonempty; ++i) 
		{
			// Determine if tile is similar
			bool same = ((tps[i].p.y == last.p.y) &&
				(tps[i].p.x == last.p.x + (tls.x * (1 + samecount))) &&
				(tps[i].c == last.c));
			
			// Check if same is true
			if (same == true) 
			{
				// Increment same count and keep going
				++samecount;
				// tps[i].c = Color::Green;
			}
			// 
			else 
			{
				// Check same count
				if (samecount) 
				{
					// Expand tile
					last.s.x = (1 + samecount) * tls.x;
				}

				// Write tile to list
				tpo.push_back(last);

				// Set same count to 0
				samecount = 0;

				// Set last to TPS at element i
				last = tps[i];
			}
		}
		// catch the last tile
		if (samecount) 
		{
			last.s.x = (1 + samecount) * tls.x;
			tpo.push_back(last);
		}

		// No scan down Y, using different algo now that compressible blocks may
		// not be contiguous
		const auto xsave = tpo.size();
		samecount = 0;
		vector<tp> tpox;
		for (size_t i = 0; i < tpo.size(); ++i)
		{
			last = tpo[i];
			for (size_t j = i + 1; j < tpo.size(); ++j)
			{
				bool same = ((tpo[j].p.x == last.p.x) && (tpo[j].s == last.s) &&
					(tpo[j].p.y == last.p.y + (tls.y * (1 + samecount))) &&
					(tpo[j].c == last.c));
				
				if (same) 
				{
					++samecount;
					tpo.erase(tpo.begin() + j);
					--j;
				}
			}
			if (samecount) 
			{
				last.s.y = (1 + samecount) * tls.y; // Expand tile
			}

			// write tile to list
			tpox.push_back(last);

			samecount = 0;
		}

		tps.swap(tpox);
	}

	for (auto& t : tps)
	{
		auto s = make_unique<sf::RectangleShape>();
		s->setPosition(t.p);
		s->setSize(t.s);
		s->setFillColor(Color::Red);
		s->setFillColor(t.c);
		// s->setFillColor(Color(rand()%255,rand()%255,rand()%255));
		_sprites.push_back(move(s));
	}

	cout << "Level with " << (_width * _height) << " Tiles, With " << nonempty
		<< " Not Empty, using: " << _sprites.size() << " Sprites\n";
}

// Render function
//
// Function for rendering tiles to window
void LevelSystem::Render(RenderWindow& window)
{
	for (auto& t : _sprites) 
	{
		window.draw(*t);
	}
}

// Get Tile Function
//
// Function returns the tile as a Vector2ul
LevelSystem::Tile LevelSystem::getTile(sf::Vector2ul p) 
{
	if (p.x > _width || p.y > _height) 
	{
		throw string("Tile out of range: ") + to_string(p.x) + "," +
			to_string(p.y) + ")";
	}
	return _tiles[(p.y * _width) + p.x];
}

// Get Width function
//
// Returns the tile width
size_t LevelSystem::getWidth()
{ 
	return _width;
}

// Get Tile Height
//
// Function returns the tile height
size_t LevelSystem::getHeight()
{ 
	return _height; 
}

// Get Tile Position
//
// Obtain the tile position as a Vector2f
sf::Vector2f LevelSystem::getTilePosition(sf::Vector2ul p) 
{
	return (Vector2f(p.x, p.y) * _tileSize) + _offset;
}

// Find Tiles function
//
// Function returns specific tiles
std::vector<sf::Vector2ul> LevelSystem::findTiles(LevelSystem::Tile type) {
	
	auto v = vector<sf::Vector2ul>();
	
	for (size_t i = 0; i < _width * _height; ++i) 
	{
		if (_tiles[i] == type) 
		{
			v.push_back({ i % _width, i / _width });
		}
	}

	return v;
}

// Get Tile At function
//
// Function returns the tile at a specific location
LevelSystem::Tile LevelSystem::getTileAt(Vector2f v) 
{
	auto a = v - _offset;

	if (a.x < 0 || a.y < 0) 
	{
		throw string("Tile out of range ");
	}

	return getTile(Vector2ul((v - _offset) / (_tileSize)));
}

// Is On Grid function
//
// Function determines if the tile is on a grid
bool LevelSystem::isOnGrid(sf::Vector2f v) 
{
	auto a = v - _offset;

	if (a.x < 0 || a.y < 0) 
	{
		return false;
	}

	auto p = Vector2ul((v - _offset) / (_tileSize));

	if (p.x > _width || p.y > _height) 
	{
		return false;
	}

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
	buildSprites();
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
	return _offset; 
}

// Get Tile Size function
//
// Function returns the size of the tiles
float LevelSystem::getTileSize() 
{ 
	return _tileSize; 
}