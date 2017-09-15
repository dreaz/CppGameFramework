#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include "Component.h"
#include <iostream>

class SpriteRenderer : public Component
{
private:
	std::shared_ptr<sf::Sprite> sprite;
	sf::Texture texture;
	bool isLoaded = false;
public:
	SpriteRenderer(std::shared_ptr<GameObject> go, std::string pathToImage);
	void Update(sf::Time deltatime) override;
	void Draw(sf::RenderWindow& window) override;
	std::shared_ptr<sf::Sprite> GetSprite();
	~SpriteRenderer();
};

#endif // !SPRITERENDERER_H

