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
			
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
			{
				//make keyboard class here that uses this for key press down & up
			}
		}

		//set the focus variable
		GameManager::GetInstance()->hasFocus = window.hasFocus();

		window.clear(sf::Color::Black);
		GameManager::GetInstance()->Update();
		GameManager::GetInstance()->Draw(window);
		window.display();
	}

	return 0;
}