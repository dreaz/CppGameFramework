#include "GameManager.h"

#include "Player.h"

GameManager* GameManager::instance = 0;

GameManager * GameManager::GetInstance()
{
	if (instance == 0)
	{
		instance = new GameManager();
	}

	return instance;

}

GameManager::GameManager()
{
	objects = new std::vector<std::shared_ptr<GameObject>>;

	std::shared_ptr<GameObject> go = std::make_shared<GameObject>(sf::Vector2f(100, 100));
	std::shared_ptr<Player> cmp = std::make_shared<Player>(go);
	go->AddComponent(cmp);
	objects->push_back(go);

	clock = new sf::Clock();

	//instantiate the network controller
	networkController = std::make_shared<NetworkController>();

	hasFocus = false;
}

void GameManager::Update()
{
	sf::Time deltatime = clock->restart();
	std::vector<std::shared_ptr<GameObject>>::iterator i;
	for (i = objects->begin(); i != objects->end(); i++)
	{
		(*i)->Update(deltatime);
	}

	
	if (!hasFocus)
	{
		return;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::H) && !networkController->isHosting)
	{
		networkController->Host();
		
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && !networkController->isClient)
	{		
		networkController->JoinLocalhost();
	}
}




void GameManager::Draw(sf::RenderWindow& window)
{
	std::vector<std::shared_ptr<GameObject>>::iterator i;
	for (i = objects->begin(); i != objects->end(); i++)
	{
		(*i)->Draw(window);
	}
}


GameManager::~GameManager()
{
}
