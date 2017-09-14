#ifndef PLAYER_H
#define PLAYER_H

#include "Component.h"
#include "GameManager.h"
#include <iostream>
#include <SFML\Graphics.hpp>

class Player : public Component
{
public:
	Player(std::shared_ptr<GameObject> go);
	void Update(sf::Time deltatime);
	void Test();
	~Player();
};

#endif // !PLAYER_H
