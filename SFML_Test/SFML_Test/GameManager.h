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
	std::vector<std::shared_ptr<GameObject>>* objectsToAdd;
	std::vector<std::shared_ptr<GameObject>>* objectsToRemove;
	sf::Clock* clock;
public:
	static GameManager* GetInstance();

	GameManager();

	void Update();
	void Draw(sf::RenderWindow& window);
	void AddObject(std::shared_ptr<GameObject> obj);
	void RemoveObject(std::shared_ptr<GameObject> obj);
	bool initilized = false;
	~GameManager();
};

#include "GameObject.h"

#endif
