#include "GameObject.h"

GameObject::GameObject(sf::Vector2f& initPos)
{
	shape = sf::CircleShape(100.f);
	shape.setPosition(initPos);
	shape.setFillColor(sf::Color::Red);

	components = new std::vector<std::shared_ptr<Component>>;
	this->setPosition(initPos);
}

void GameObject::Update(sf::Time deltatime)
{
	std::vector<std::shared_ptr<Component>>::iterator i;
	for (i = components->begin(); i != components->end(); i++)
	{
		(*i)->Update(deltatime);
	}
	shape.setPosition(this->getPosition());
}

void GameObject::Draw(sf::RenderWindow& window)
{
	std::vector<std::shared_ptr<Component>>::iterator i;
	for (i = components->begin(); i != components->end(); i++)
	{
		(*i)->Draw(window);
	}
	window.draw(shape);
}

void GameObject::AddComponent(std::shared_ptr<Component> cmp)
{
	components->push_back(cmp);
}


GameObject::~GameObject()
{
}
