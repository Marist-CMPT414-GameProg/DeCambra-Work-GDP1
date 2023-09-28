#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Striker
{
private:
	Vector2f m_Position;

	// A CircleShape object
	CircleShape m_Shape;

	sf::Sprite m_Sprite;

	float m_Speed = 500;

	bool m_MovingRight = false;
	bool m_MovingLeft = false;
	bool m_MovingUp = false;
	bool m_MovingDown = false;


public:
	Striker(float startX, float startY);

	FloatRect getPosition();

	CircleShape getShape();

	Sprite getSprite();

	float getXVelocity() const;
	float getYVelocity() const;

	void setSpritePosition(float newX, float newY)
	{
		m_Sprite.setPosition(newX, newY);
	}

	void setShapeOrigin()
	{
		m_Shape.setOrigin(93, 93);
	}

	void setTexture(sf::Texture const& texture)
	{
		m_Sprite.setTexture(texture);
	}

	void moveLeft();
	void moveRight();
	void stopLeft();
	void stopRight();

	void moveUp();
	void moveDown();
	void stopUp();
	void stopDown();

	void update(Time dt);
};