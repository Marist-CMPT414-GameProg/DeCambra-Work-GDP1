#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Striker
{
private:
	Vector2f m_Position;

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

	float getRadius();

	float getXVelocity() const;
	float getYVelocity() const;
	float getYPosition();
	float getXPosition();

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

	void setXPosition(float newX);

	void moveLeft(Time dt, float i);
	void moveRight(Time dt, float i);
	void stopLeft();
	void stopRight();

	void moveUp(Time dt, float i);
	void moveDown(Time dt, float i);
	void stopUp();
	void stopDown();

	void Goal(float newY, float newX);
	void update(Time dt);
};