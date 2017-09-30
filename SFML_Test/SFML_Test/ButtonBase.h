#ifndef BUTTONBASE_H
#define BUTTONBASE_H

#include <SFML\Graphics.hpp>
#include <memory>
#include <functional>

#include "Component.h"
#include "GameObject.h"

/// <summary>
/// "Button" class was taken apparantly
/// </summary>
class ButtonBase : public Component
{
public:
	ButtonBase(std::shared_ptr<GameObject> go, sf::Vector2f size, std::function<void(void)> callback);
	~ButtonBase();

	void Update(sf::Time deltatime) override;
	void Draw(sf::RenderWindow & window) override;

	bool MouseDown = false;

	std::function<void(void)> callback;

private:
	std::shared_ptr<sf::FloatRect> buttonRectangle;
};

#endif // !BUTTONBASE_H