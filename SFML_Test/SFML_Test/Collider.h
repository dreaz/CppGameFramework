#ifndef COLLIDER_H
#define COLLIDER_H
#include "Component.h"

class SpriteRenderer;

class Collider : public Component, std::enable_shared_from_this<Collider>
{
private:
	std::shared_ptr<SpriteRenderer> spriteRenderer;
	void CheckCollisions();
	sf::Color color;
public:
	Collider(std::shared_ptr<GameObject> go, bool doCollisionChecks);
	std::shared_ptr<sf::FloatRect> collisionBox;
	void Update(sf::Time deltatime) override;
	void Draw(sf::RenderWindow & window) override;

	bool DoCollisionChecks;

	~Collider();
};

#include "SpriteRenderer.h"

#endif // !COLLIDER_H

