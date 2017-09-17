#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <SFML\Graphics.hpp>


class Vector2D
{
public:
	static sf::Vector2f Lerp(sf::Vector2f from, sf::Vector2f to, float t);
};

#endif