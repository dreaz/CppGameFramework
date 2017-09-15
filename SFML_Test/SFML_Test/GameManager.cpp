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
	objectsToAdd = new std::vector<std::shared_ptr<GameObject>>;
	objectsToRemove = new std::vector<std::shared_ptr<GameObject>>;

	player = std::make_shared<GameObject>(sf::Vector2f(100, 100));
	std::shared_ptr<Player> cmp = std::make_shared<Player>(player);
	player->AddComponent(cmp);
	this->AddObject(player);
	std::shared_ptr<Player> cmp1 = std::dynamic_pointer_cast<Player>((player->GetComponent("PlayerCmp")));
	//cmp1->Test();
	//go->RemoveComponent("PlayerCmp");

	clock = new sf::Clock();

	//instantiate the network controller
	networkController = std::make_shared<NetworkController>();

	hasFocus = false;
	once = false;

	std::cout << "Press H to host\nOr press C to connect." << std::endl;
}

void GameManager::Update()
{
	sf::Time deltatime = clock->restart();

	//Remove Objects
	for (std::shared_ptr<GameObject> go : (*objectsToRemove))
	{
		objects->erase(std::remove(objects->begin(), objects->end(), go), objects->end());
	}
	objectsToRemove->clear();

	//Add Objects
	objects->insert(objects->end(), objectsToAdd->begin(), objectsToAdd->end());
	objectsToAdd->clear();

	std::vector<std::shared_ptr<GameObject>>::iterator i;
	for (i = objects->begin(); i != objects->end(); i++)
	{
		(*i)->Update(deltatime);
	}

	
	//Has focus is because that you can use the same keyboard for multiple windows, which really make multiplayer testing annoying.
	if (!hasFocus)
	{
		return;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::H) && !once)
	{
		once = true;
		networkController->StartServer();
		
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && !once)
	{		
		once = true;
		std::shared_ptr<NetworkedPlayer> cmp = std::make_shared<NetworkedPlayer>(player);
		player->AddComponent(cmp);
		cmp->JoinServer();
	}
	//Redo me to use input system
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		std::shared_ptr<NetworkedPlayer> cmp1 = std::dynamic_pointer_cast<NetworkedPlayer>((player->GetComponent("NetworkedPlayerCmp")));
		cmp1->Disconnect();
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

void GameManager::AddObject(std::shared_ptr<GameObject> obj)
{
	objectsToAdd->push_back(obj);
}

void GameManager::RemoveObject(std::shared_ptr<GameObject> obj)
{
	if (!(std::find(objectsToRemove->begin(), objectsToRemove->end(), obj) != objectsToRemove->end()))
	{
		objectsToRemove->push_back(obj);
	}
}


GameManager::~GameManager()
{
	delete objects;
	delete objectsToAdd;
	delete objectsToRemove;	
}
