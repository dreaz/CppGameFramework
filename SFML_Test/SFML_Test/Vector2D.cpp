#include "Vector2D.h"


sf::Vector2f Vector2D::Lerp(sf::Vector2f from, sf::Vector2f to, float t)
{
	return (1 - t) * from + t * to;
}