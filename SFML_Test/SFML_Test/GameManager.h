#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <SFML\Graphics.hpp>
#include <vector>
#include <memory>
#include "NetworkController.h"

class GameObject;
class Collider;

class GameManager
{
private:
	static GameManager *instance;
	std::vector<std::shared_ptr<GameObject>>* objects;
	std::vector<std::shared_ptr<GameObject>>* objectsToAdd;
	std::vector<std::shared_ptr<GameObject>>* objectsToRemove;

	std::vector<std::shared_ptr<Collider>>* colliders;
	std::vector<std::shared_ptr<Collider>>* collidersToAdd;
	std::vector<std::shared_ptr<Collider>>* collidersToRemove;

	sf::Clock* clock;
public:
	static GameManager* GetInstance();

	GameManager();

	void Update();
	void Draw(sf::RenderWindow& window);

	void AddObject(std::shared_ptr<GameObject> obj);
	void RemoveObject(std::shared_ptr<GameObject> obj);

	bool hasFocus;
	bool once;


	void AddCollider(std::shared_ptr<Collider> obj);
	void RemoveCollider(std::shared_ptr<Collider> obj);
	std::vector<std::shared_ptr<Collider>>* GetColliders();

	std::shared_ptr<GameObject> FindObjectByTag(std::string tag);


	bool initilized = false;
	~GameManager();
};

#include "GameObject.h"
#include "Collider.h"

#endif
