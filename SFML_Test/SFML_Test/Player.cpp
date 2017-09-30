#include "Player.h"



Player::Player(std::shared_ptr<GameObject> go) : Component(go, "PlayerCmp")
{
	GetGameObject()->Tag = "Player";
	physics = std::dynamic_pointer_cast<Physics2D>((GetGameObject()->GetComponent("Physics")));
}

void Player::Update(sf::Time deltatime)
{
	if (!GameManager::GetInstance()->hasFocus)
	{
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		GetGameObject()->setRotation(50);
		physics->SetVelocity(sf::Vector2f(0, -300));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		physics->SetVelocity(sf::Vector2f(0, 300));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		physics->SetVelocity(sf::Vector2f(-300,0));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		physics->SetVelocity(sf::Vector2f(300, 0));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		physics->SetVelocity(sf::Vector2f(0, 0));
	}
}

void Player::Test()
{
	std::cout << "Test";
}


Player::~Player()
{
}
