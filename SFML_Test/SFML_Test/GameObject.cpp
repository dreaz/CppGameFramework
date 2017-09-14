#include "GameObject.h"

GameObject::GameObject(sf::Vector2f& initPos)
{
	shape = sf::CircleShape(100.f);
	shape.setPosition(initPos);
	shape.setFillColor(sf::Color::Red);

	components = new std::vector<std::shared_ptr<Component>>;
	componentsToRemove = new std::vector<std::shared_ptr<Component>>;
	this->setPosition(initPos);
}

void GameObject::Update(sf::Time deltatime)
{
	//Remove Components from componentsToRemove
	for (std::shared_ptr<Component> cmp : (*componentsToRemove))
	{
		components->erase(std::remove(components->begin(), components->end(), cmp), components->end());
	}
	componentsToRemove->clear();

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

std::shared_ptr<Component> GameObject::GetComponent(std::string cmp)
{
	std::vector<std::shared_ptr<Component>>::iterator i;
	for (i = components->begin(); i != components->end(); i++)
	{
		if ((*i)->GetType() == cmp)
		{
			return (*i);
		}
	}
	return nullptr;
}

void GameObject::RemoveComponent(std::string cmp)
{
	std::vector<std::shared_ptr<Component>>::iterator i;
	for (i = components->begin(); i != components->end(); i++)
	{
		if ((*i)->GetType() == cmp)
		{
			componentsToRemove->push_back((*i));
			return;
		}
	}
}

GameObject::~GameObject()
{
	delete components;
}
