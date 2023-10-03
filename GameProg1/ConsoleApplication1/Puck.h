#pragma once
#include <SFML/Graphics.hpp>
#include "Striker.h"

using namespace sf;

class Puck
{
private:
	Vector2f m_Position;
	CircleShape m_Shape;

	sf::Sprite m_Sprite;

	sf::Vector2f m_InitialVelocity;

	float m_Speed = 55;
	float m_DirectionX = .2f;
	float m_DirectionY = .2f;

	bool m_Colliding = false;

	float m_LastDistance;

public:
	Puck(float startX, float startY);

	FloatRect getPosition();
	CircleShape getShape();
	Sprite getSprite();

	float getXVelocity();
	float getYPosition();
	float getXPosition();

	void isColliding();
	void notColliding();

	void setVelocity(float x, float y);

	void setTexture(sf::Texture const& texture)
	{
		m_Sprite.setTexture(texture);
	}

	void setSpritePosition(float newX, float newY)
	{
		m_Sprite.setPosition(newX, newY);
	}

	void setShapeOrigin()
	{
		m_Shape.setOrigin(54.5, 54.5);
	}

	void setYPositionTop();
	void setYPositionBottom();
	void setXPositionRight();
	void setXPositionLeft();

	void reboundSides();
	void reboundBottomOrTop();
	void reboundStriker(Striker& striker);

	void Goal();
	void update(Time dt);
};