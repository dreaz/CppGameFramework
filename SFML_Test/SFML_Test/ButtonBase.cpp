#include "ButtonBase.h"



ButtonBase::ButtonBase(std::shared_ptr<GameObject> go, sf::Vector2f size, std::function<void()> callback) : Component(go, "ButtonBase")
{
	//sRect (const Vector2< T > &position, const Vector2< T > &size)
	buttonRectangle = std::make_shared<sf::FloatRect>(GetGameObject()->getPosition(),size);	
	this->callback = callback;

}


ButtonBase::~ButtonBase()
{
}

void ButtonBase::Update(sf::Time deltatime)
{
	
}

void ButtonBase::Draw(sf::RenderWindow & window)
{
	sf::RectangleShape colBox;
	colBox.setSize(sf::Vector2f(buttonRectangle->width, buttonRectangle->height));
	colBox.setPosition(GetGameObject()->getPosition());
	colBox.setOutlineThickness(1);
	colBox.setOutlineColor(sf::Color::Blue);
	colBox.setFillColor(sf::Color::Cyan	);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !MouseDown)
	{
		//Only capture one frame of mouse press
		MouseDown = true;
		//get the mouse position
		sf::Vector2f mousePos(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
		if (buttonRectangle->contains(mousePos))
		{
			std::cout << "Inside the button" << std::endl;
			//call the callback
			callback();
		}
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		//untoggle if mouse is not pressed
		MouseDown = false;
	}


	window.draw(colBox);
}
