#include "GameManager.h"

#include "Player.h"
#include "SpriteRenderer.h"
#include "Physics2D.h"
#include "Collider.h"
#include "ButtonBase.h"

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

	colliders = new std::vector<std::shared_ptr<Collider>>;
	collidersToAdd= new std::vector<std::shared_ptr<Collider>>;
	collidersToRemove = new std::vector<std::shared_ptr<Collider>>;

	//Make GameObject and add Components
	std::shared_ptr<GameObject> go = std::make_shared<GameObject>(sf::Vector2f(100, 100));
	std::shared_ptr<Physics2D> cmp3 = std::make_shared<Physics2D>(go);
	go->AddComponent(cmp3);
	std::shared_ptr<Player> cmp = std::make_shared<Player>(go);
	go->AddComponent(cmp);
	std::shared_ptr<SpriteRenderer> cmp2 = std::make_shared<SpriteRenderer>(go, "sprites/box.png");
	go->AddComponent(cmp2);
	std::shared_ptr<Collider> cmp4 = std::make_shared<Collider>(go, true);
	AddCollider(cmp4);
	go->AddComponent(cmp4);

	std::shared_ptr<GameObject> go2 = std::make_shared<GameObject>(sf::Vector2f(400, 200));
	std::shared_ptr<SpriteRenderer> c1 = std::make_shared<SpriteRenderer>(go2, "sprites/box.png");
	go2->AddComponent(c1);
	std::shared_ptr<Collider> c2 = std::make_shared<Collider>(go2, true);
	AddCollider(c2);
	go2->AddComponent(c2);

	//Add a test button
	std::shared_ptr<GameObject> button = std::make_shared<GameObject>(sf::Vector2f(400, 100));
	std::shared_ptr<ButtonBase> buttonCMP = std::make_shared<ButtonBase>(button, sf::Vector2f(400,100), std::bind(&GameManager::ButtonCallbackTest, this));
	button->AddComponent(buttonCMP);
	this->AddObject(button);


	//Set Scale
	go->setScale(sf::Vector2f(.5f, .5f));
	go2->setScale(sf::Vector2f(.5f, .5f));

	this->AddObject(go);
	this->AddObject(go2);


	//std::shared_ptr<Player> cmp1 = std::dynamic_pointer_cast<Player>((go->GetComponent("PlayerCmp")));
	//cmp1->Test();
	//go->RemoveComponent("PlayerCmp");

	initilized = true;
	clock = new sf::Clock();
}

void GameManager::Update()
{
	sf::Time deltatime = clock->restart();


	//Add Objects
	objects->insert(objects->end(), objectsToAdd->begin(), objectsToAdd->end());
	objectsToAdd->clear();

	//Add Colliders
	colliders->insert(colliders->end(), collidersToAdd->begin(), collidersToAdd->end());
	collidersToAdd->clear();

	//Remove Objects
	for (std::shared_ptr<GameObject> go : (*objectsToRemove))
	{
		objects->erase(std::remove(objects->begin(), objects->end(), go), objects->end());
	}
	objectsToRemove->clear();

	//Remove Colliders
	for (std::shared_ptr<Collider> col : (*collidersToRemove))
	{
		colliders->erase(std::remove(colliders->begin(), colliders->end(), col), colliders->end());
	}
	collidersToRemove->clear();

	std::vector<std::shared_ptr<GameObject>>::iterator i;
	for (i = objects->begin(); i != objects->end(); i++)
	{
		(*i)->Update(deltatime);
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


void GameManager::ButtonCallbackTest()
{
	std::cout << "SUP" << std::endl;
}

void GameManager::AddCollider(std::shared_ptr<Collider> obj)
{
	collidersToAdd->push_back(obj);
}

void GameManager::RemoveCollider(std::shared_ptr<Collider> obj)
{
	collidersToRemove->push_back(obj);
}

std::vector<std::shared_ptr<Collider>>* GameManager::GetColliders()
{
	return colliders;
}

std::shared_ptr<GameObject> GameManager::FindObjectByTag(std::string tag)
{
	std::vector<std::shared_ptr<GameObject>>::iterator i;
	for (i = objects->begin(); i != objects->end(); i++)
	{
		if ((*i)->Tag == tag)
		{
			return std::shared_ptr<GameObject>();			
		}
	}
	return NULL;	
}

GameManager::~GameManager()
{
	delete objects;
	delete objectsToAdd;
	delete objectsToRemove;

	delete colliders;
	delete collidersToAdd;
	delete collidersToRemove;
}
