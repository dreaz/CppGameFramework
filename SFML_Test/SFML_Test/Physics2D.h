#ifndef PHYSICS2D_H
#define PHYSICS2D_H

#include "Component.h"
#include <iostream>

class Physics2D : public Component
{
private:
	std::shared_ptr<sf::Vector2f> velocity;
	std::shared_ptr<sf::Vector2f> gravity = std::make_shared<sf::Vector2f>(0,9.87f);
public:
	Physics2D(std::shared_ptr<GameObject> go);
	void Update(sf::Time deltatime);
	void SetVelocity(sf::Vector2f newVelocity);
	sf::Vector2f GetVelocity();
	~Physics2D();
};
#endif // !PHYSICS2D_H

