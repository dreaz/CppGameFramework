#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <SFML\Graphics.hpp>
#include <memory>
#include <string>

class Component;

class GameObject : public sf::Transformable
{
private:
	sf::CircleShape shape;
	std::vector<std::shared_ptr<Component>>* components;
public:
	GameObject(sf::Vector2f& initPos);
	void Update(sf::Time deltatime);
	void Draw(sf::RenderWindow& window);
	void AddComponent(std::shared_ptr<Component> cmp);
	std::string Tag;
	~GameObject();
};


#include"Component.h"
#endif // !GAMEOBJECT_H