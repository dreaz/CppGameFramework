#include "ButtonBase.h"



ButtonBase::ButtonBase(std::shared_ptr<GameObject> go, sf::Vector2f size, sf::String buttonLabel, std::function<void()> callback) : Component(go, "ButtonBase")
{
	//sRect (const Vector2< T > &position, const Vector2< T > &size)
	buttonRectangle = std::make_shared<sf::FloatRect>(GetGameObject()->getPosition(),size);	
	this->callback = callback;
	
	ButtonText = std::make_shared<sf::Text>();
	Font = std::make_shared<sf::Font>();
	// Declare and load a font
	if (!Font->loadFromFile("fonts/opensanslight.ttf"))
	{
		//error
		std::cout << "Error loading font";
		return;
	}
	FontLoaded = true;
	

	// select the font
	ButtonText->setFont((*Font));
	// set the string to display
	ButtonText->setString(buttonLabel);
	// set the character size
	ButtonText->setCharacterSize(25); // in pixels, not points!
	 // set the color
	ButtonText->setFillColor(sf::Color::Black);
	// set the text style
	//ButtonText->setStyle(sf::Text::Bold | sf::Text::Underlined);
	sf::FloatRect textRect = ButtonText->getLocalBounds();
	ButtonText->setOrigin(textRect.left + textRect.width / 2.0f,	textRect.top + textRect.height / 2.0f);
	//sf::Vector2f textPosition(GetGameObject()->getPosition().x + (buttonRectangle->width / 2), GetGameObject()->getPosition().y + (buttonRectangle->height / 2));
	sf::Vector2f textPosition(GetGameObject()->getPosition().x + (buttonRectangle->width / 2), GetGameObject()->getPosition().y + (buttonRectangle->height / 2));

	ButtonText->setPosition(textPosition);

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

	if (FontLoaded)
	{
		window.draw((*ButtonText));
	}
}
