#ifndef PLAYER_H
#define PLAYER_H

#include "Component.h"
#include "GameManager.h"
#include <iostream>
#include <SFML\Graphics.hpp>

class Physics2D;

class Player : public Component
{
private:
	std::shared_ptr<Physics2D> physics;
public:
	Player(std::shared_ptr<GameObject> go);
	void Update(sf::Time deltatime);
	void Test();
	~Player();
};

#include "Physics2D.h"

#endif // !PLAYER_H
