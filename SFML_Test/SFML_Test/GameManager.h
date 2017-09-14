#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <SFML\Graphics.hpp>
#include <vector>
#include <memory>
#include "NetworkController.h"

class GameObject;
class GameManager
{
private:
	static GameManager *instance;
	std::vector<std::shared_ptr<GameObject>>* objects;
	std::vector<std::shared_ptr<GameObject>>* objectsToAdd;
	std::vector<std::shared_ptr<GameObject>>* objectsToRemove;
	sf::Clock* clock;
	std::shared_ptr<NetworkController> networkController;

	std::shared_ptr<GameObject> player;
public:
	static GameManager* GetInstance();

	GameManager();

	void Update();
	void Draw(sf::RenderWindow& window);
	void AddObject(std::shared_ptr<GameObject> obj);
	void RemoveObject(std::shared_ptr<GameObject> obj);

	bool hasFocus;
	bool once;


	~GameManager();
};

#include "GameObject.h"

#endif
