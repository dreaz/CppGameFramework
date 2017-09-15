#include "Physics2D.h"



Physics2D::Physics2D(std::shared_ptr<GameObject> go) : Component(go, "Physics")
{
	velocity = std::make_shared<sf::Vector2f>(0.f, 0.f);
}

void Physics2D::Update(sf::Time deltatime)
{
	sf::Vector2f movement = (*velocity);
	movement += (*gravity);
	movement *= deltatime.asSeconds();
	GetGameObject()->move(movement);
}

void Physics2D::SetVelocity(sf::Vector2f newVelocity)
{
	if (velocity)
		(*velocity) = newVelocity;
}

sf::Vector2f Physics2D::GetVelocity()
{
	return (*velocity);
}


Physics2D::~Physics2D()
{
}
