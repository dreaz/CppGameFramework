#include "SpriteRenderer.h"



SpriteRenderer::SpriteRenderer(std::shared_ptr<GameObject> go, std::string pathToImage) : Component(go, "SpriteRenderer")
{
	if (!texture.loadFromFile(pathToImage))
	{
		//error
		std::cout << "Error loading image";
		return;
	}
	isLoaded = true;
	sprite = std::make_shared<sf::Sprite>();
	sprite->setTexture(texture);
	//set the origin to the center
	GetGameObject()->setOrigin(sprite->getLocalBounds().width / 2, sprite->getLocalBounds().height / 2);
}

void SpriteRenderer::Update(sf::Time deltatime)
{
	if (isLoaded)
	{
		sprite->setPosition(GetGameObject()->getPosition());
		sprite->setRotation(GetGameObject()->getRotation());
		sprite->setScale(GetGameObject()->getScale());
	}
}

void SpriteRenderer::Draw(sf::RenderWindow & window)
{
	if (isLoaded)
		window.draw((*sprite));
}

std::shared_ptr<sf::Sprite> SpriteRenderer::GetSprite()
{
	return sprite;
}


SpriteRenderer::~SpriteRenderer()
{
}
