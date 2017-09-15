#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <memory>
#include <SFML\Graphics.hpp>

class GameObject;

class Component
{
private:
	std::shared_ptr<GameObject> gameObject;
	std::string type = "Cmp";
public:
	Component(std::shared_ptr<GameObject> go, std::string type);
	std::shared_ptr<GameObject> GetGameObject();
	virtual void Update(sf::Time deltaTime);
	virtual void Draw(sf::RenderWindow& window);
	virtual void OnCollision(std::shared_ptr<GameObject> other);
	std::string GetType();
	~Component();
};

#include "GameObject.h"
#endif

