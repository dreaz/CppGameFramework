#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <SFML\Graphics.hpp>
#include <vector>
#include <memory>
class GameObject;
class GameManager
{
private:
	static GameManager *instance;
	std::vector<std::shared_ptr<GameObject>>* objects;
	sf::Clock* clock;
public:
	static GameManager* GetInstance();

	GameManager();

	void Update();
	void Draw(sf::RenderWindow& window);

	~GameManager();
};

#include "GameObject.h"

#endif
