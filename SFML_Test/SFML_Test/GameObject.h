#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <SFML\Graphics.hpp>
#include <memory>
#include <string>
#include "GameManager.h"

class Component;

class GameObject : public sf::Transformable
{
private:
	std::vector<std::shared_ptr<Component>>* components;
	std::vector<std::shared_ptr<Component>>* componentsToRemove;
public:
	GameObject(sf::Vector2f& initPos);
	void Update(sf::Time deltatime);
	void Draw(sf::RenderWindow& window);
	void OnCollision(std::shared_ptr<GameObject> other);
	void AddComponent(std::shared_ptr<Component> cmp);
	std::shared_ptr<Component> GetComponent(std::string cmp);
	void RemoveComponent(std::string cmp);
	std::string Tag;
	~GameObject();
};


#include"Component.h"
#endif // !GAMEOBJECT_H