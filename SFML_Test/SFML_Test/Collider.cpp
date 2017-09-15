#include "Collider.h"




Collider::Collider(std::shared_ptr<GameObject> go, bool doCollisionChecks) : Component(go,"Collider")
{
	this->DoCollisionChecks = doCollisionChecks;
	spriteRenderer = std::dynamic_pointer_cast<SpriteRenderer>((GetGameObject()->GetComponent("SpriteRenderer")));
	collisionBox = std::make_shared<sf::FloatRect>(spriteRenderer->GetSprite()->getGlobalBounds());
}

void Collider::CheckCollisions()
{
	GameManager * gm = GameManager::GetInstance();

	if (DoCollisionChecks)
	{
		for (std::vector<std::shared_ptr<Collider>>::iterator it = gm->GetColliders()->begin(); it != gm->GetColliders()->end(); it++)
		{
			if (it->get() != this || !(*it)->DoCollisionChecks)
			{
				if (collisionBox->intersects((*(*it)->collisionBox)))
				{
					GetGameObject()->OnCollision((*it)->GetGameObject());
					color = sf::Color::Red;
				}
				else
				{
					color = sf::Color::Green;
				}
			}
		}
	}
}

void Collider::Update(sf::Time deltatime)
{
	collisionBox = std::make_shared<sf::FloatRect>(spriteRenderer->GetSprite()->getGlobalBounds());
	CheckCollisions();
}

void Collider::Draw(sf::RenderWindow & window)
{
	sf::RectangleShape colBox;
	colBox.setSize(sf::Vector2f(collisionBox->height, collisionBox->width));
	colBox.setPosition(GetGameObject()->getPosition());
	colBox.setOutlineThickness(1);
	colBox.setOutlineColor(color);
	colBox.setFillColor(sf::Color::Transparent);

	window.draw(colBox);
}


Collider::~Collider()
{
}
