#include "Striker.h"

// This the constructor and it is called when we create an object
Striker::Striker(float startX, float startY)
{
	m_Position.x = startX;
	m_Position.y = startY;

	m_Shape.setRadius(93);
	m_Shape.setPosition(m_Position);
}

FloatRect Striker::getPosition()
{
	return m_Shape.getGlobalBounds();
}

CircleShape Striker::getShape()
{
	return m_Shape;
}

Sprite Striker::getSprite()
{
	return m_Sprite;
}

float Striker::getRadius()
{
	return m_Shape.getRadius();
}

float Striker::getXVelocity() const
{
	return m_MovingRight - m_MovingLeft;
}

float Striker::getYVelocity() const
{
	return m_MovingDown - m_MovingUp;
}

float Striker::getYPosition()
{
	return m_Position.y;
}

float Striker::getXPosition()
{
	return m_Position.x;
}

void Striker::setXPosition(float newX)
{
	m_Position.x = newX;
}

void Striker::moveLeft(Time dt, float i)
{
	m_MovingLeft = true;
	if (m_MovingLeft && m_Position.x > i)
	{
		m_Position.x -= m_Speed * dt.asSeconds();
	}
}

void Striker::moveRight(Time dt, float i)
{
	m_MovingRight = true;
	if (m_MovingRight && m_Position.x < i)
	{
		m_Position.x += m_Speed * dt.asSeconds();
	}
}

void Striker::stopLeft()
{
	m_MovingLeft = false;
}

void Striker::stopRight()
{
	m_MovingRight = false;
}

void Striker::moveUp(Time dt, float i)
{
	m_MovingUp = true;
	if (m_MovingUp && m_Position.y > i)
	{
		m_Position.y -= m_Speed * dt.asSeconds();
	}
}

void Striker::moveDown(Time dt, float i)
{
	m_MovingDown = true;
	if (m_MovingDown && m_Position.y < i)
	{
		m_Position.y += m_Speed * dt.asSeconds();
	}
}

void Striker::stopUp()
{
	m_MovingUp = false;
}

void Striker::stopDown()
{
	m_MovingDown = false;
}

void Striker::Goal(float newY, float newX)
{
	m_Position.x = newX;
	m_Position.y = newY;
}

void Striker::update(Time dt)
{
	m_Shape.setPosition(m_Position);
	m_Shape.setFillColor(sf::Color::Transparent);
}

//93 to outer striker
//43 top and bottom of screen
//38 sides of screen