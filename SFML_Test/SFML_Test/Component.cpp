#include "Component.h"


Component::Component(std::shared_ptr<GameObject> go, std::string type)
{
	this->gameObject = go;
	this->type = type;
}

std::shared_ptr<GameObject> Component::GetGameObject()
{
	return gameObject;
}

void Component::Update(sf::Time deltaTime)
{
}


void Component::Draw(sf::RenderWindow& window)
{
}

std::string Component::GetType()
{
	return type;
}

Component::~Component()
{
}
