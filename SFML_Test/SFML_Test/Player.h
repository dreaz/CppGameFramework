#ifndef PLAYER_H
#define PLAYER_H

#include "Component.h"
#include <SFML\Graphics.hpp>

class Player : public Component
{
public:
	Player(std::shared_ptr<GameObject> go);
	void Update(sf::Time deltatime);
	~Player();
};

#endif // !PLAYER_H
