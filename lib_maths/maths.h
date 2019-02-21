#pragma once

#define M_PI           3.14159265358979323846

#include <cmath>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>

namespace sf {
	// Create a definition for a sf::vector usong size_t types
	typedef Vector2<size_t> Vector2ul;
	// Return the length of a sf::vecotr
	template <typename T> double length(const Vector2<T> &v) {
		return sqrt(v.x * v.x + v.y * v.y);
	}
	// Return normalized sf::vector
	template <typename T> Vector2<T> normalize(const Vector2<T> &v) {
		Vector2<T> vector;
		double l = length(v);
		if (l != 0) {
			vector.x = v.x / length(v.x);
			vector.y = v.y / length(v.y);
		}
		return vector;
	}
	// Allow casting from one sf::vector internal type to another
	template <typename T, typename U> Vector2<T> Vcast(const Vector2<U> &v) {
		return Vector2<T>(static_cast<T>(v.x), static_cast<T>(v.y));
	}
	// Degrees to radiants conversion
	static double deg2rad(double degrees) {
		return degrees * M_PI / 180;
	}
	// Rotate a sf::vector by an angle (degrees)
	template <typename T> Vector2<T> rotate(const Vector2<T> &v, const double degrees) {
		const double theta = deg2rad(degrees);
		const double cs = cos(theta);
		const double sn = sin(theta);
		return { (T)(v.x  *cs - v.y * sn), (T)(v.x * sn + v.y * cs) };
	}
	// Allow sf::vectors to be count'ed
	template <typename T> std::ostream &operator<<(std::ostream &os, const Vector2<T> &v) {
		os << '(' << v.x << ', ' << v.y << ')';
		return os;
	}
}