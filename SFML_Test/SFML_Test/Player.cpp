#include "Player.h"



Player::Player(std::shared_ptr<GameObject> go) : Component(go, "PlayerCmp")
{
	GetGameObject()->Tag = "Player";
}

void Player::Update(sf::Time deltatime)
{
	if (!GameManager::GetInstance()->hasFocus)
	{
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		GetGameObject()->move(sf::Vector2f(0,-300 * deltatime.asSeconds()));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		GetGameObject()->move(sf::Vector2f(0, 300 * deltatime.asSeconds()));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		GetGameObject()->move(sf::Vector2f(-300 * deltatime.asSeconds(), 0));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		GetGameObject()->move(sf::Vector2f(300 * deltatime.asSeconds(), 0));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		GameManager::GetInstance()->RemoveObject(GetGameObject());
	}
}

void Player::Test()
{
	std::cout << "Test";
}


Player::~Player()
{
}
