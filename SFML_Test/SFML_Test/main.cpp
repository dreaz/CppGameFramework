#include <SFML\Graphics.hpp>
#include "GameManager.h"
#include "GameObject.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Test Game");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::LostFocus)
			{
				GameManager::GetInstance()->hasFocus = false;
			}
			else if (event.type == sf::Event::GainedFocus)
			{
				GameManager::GetInstance()->hasFocus = true;
			}
		}

		window.clear(sf::Color::Black);
		GameManager::GetInstance()->Update();
		GameManager::GetInstance()->Draw(window);
		window.display();
	}

	return 0;
}