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
 * Date Last Modified: 15/03/2020
 * -------------------------------------
 * MATHS - maths.h
 *
 * Header file for custom maths functions
 *
 */

// Libraries
#pragma once

#include <SFML/System.hpp>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
#include <sstream>
#include <vector>

// Name space
using namespace std; // Standard namesapce

// Declare namespace definition
namespace sf
{
	// Value of pi (in decimal format)
	const double PI = 3.14159265358979323846;

	// Definition for vector using size_t types
	typedef Vector2<size_t> Vector2ul;

	// Returns a length of a vector
	template <typename T> double length(const Vector2<T> &v)
	{
		// Use Ecludian formula for length
		return sqrt((v.x * v.x) + (v.y * v.y));
	}

	// Returns a normalised vector
	template <typename T> Vector2f normalize(const Vector2<T> &v)
	{
		// Create empty vector
		Vector2<T> vector;

		// Determine the length of the vector
		double l = length(v);

		// Check length does not equal 0
		if (l != 0)
		{
			// Determine normalized x value of vector
			vector.x = v.x / l;

			// Determine normalized y value of vector
			vector.y = v.y / l;
		}

		// Return the vector
		return vector;
	}

	// Allow casting from one vector internal type to another
	template <typename T, typename U>
	Vector2<T> Vcast(const Vector2<U> &v)
	{
		return Vector2<T>(static_cast<T>(v.x), static_cast<T>(v.y));
	};

	// Convert degrees to radians
	static double deg2rad(double degrees)
	{
		return degrees * (PI / 180);
	}

	// Rotate a vector by an angle(degrees)
	template <typename T>
	Vector2<T> rotate(const Vector2<T> &v, const double degrees)
	{
		// Determine theta (in rads)
		const double theta = deg2rad(degrees);

		// Cosine of the angle
		const double cs = cos(theta);

		// Sine of the angle
		const double sn = sin(theta);

		// Return rotation
		return { (T)(v.x * cs - v.y * sn), (T)(v.x * sn + v.y * cs) };
	}

	// Operator template
	template <typename T>
	Vector2<T> operator*(const Vector2<T>& left, const Vector2<T>& right)
	{
		Vector2<T> r = left;
		r.x *= right.x;
		r.y *= right.y;
		return r;
	}

	// Allow vectors to be output to console
	template <typename T>
	ostream &operator<<(ostream &os, const Vector2<T> &v)
	{
		// Create output stream
		os << '(' << v.x << ',' << v.y << ')';

		// Return output stream
		return os;
	}
}

// Operator template
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) 
{
	os << "vec[";

	for (const auto& a : v) 
	{
		os << a << ',';
	}
	os << ']';
	return os;
}

// To String Decimal Point
template <typename T>
string toStrDecPt(const uint16_t& dp, const T& i) 
{
	// String stream object
	stringstream stream;
	stream << fixed << setprecision(dp) << i;
	return stream.str();
}