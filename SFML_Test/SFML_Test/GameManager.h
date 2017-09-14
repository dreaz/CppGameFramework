#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <SFML\Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <memory>
#include "NetworkController.h"
class GameObject;
class GameManager
{
private:
	static GameManager *instance;
	std::vector<std::shared_ptr<GameObject>>* objects;
	sf::Clock* clock;

	//network controller
	std::shared_ptr<NetworkController> networkController;

	
public:
	static GameManager* GetInstance();

	GameManager();

	void Update();
	void Draw(sf::RenderWindow& window);
	bool hasFocus;

	~GameManager();
};

#include "GameObject.h"

#endif
