#include "Striker.h"

// This the constructor and it is called when we create an object
Striker::Striker(float startX, float startY)
{
	m_Position.x = startX;
	m_Position.y = startY;

	m_Shape.setRadius(60);
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

float Striker::getXVelocity() const
{
	return m_MovingRight - m_MovingLeft;
}

float Striker::getYVelocity() const
{
	return m_MovingDown - m_MovingUp;
}
void Striker::setYPositionTop()
{
	m_Position.y = 283.6;
}

void Striker::setYPositionBottom()
{
	m_Position.y = 796.4;
}

void Striker::setXPosition()
{
	m_Position.x = 1679.8;
}

void Striker::moveLeft()
{
	m_MovingLeft = true;
}

void Striker::moveRight()
{
	m_MovingRight = true;
}

void Striker::stopLeft()
{
	m_MovingLeft = false;
}

void Striker::stopRight()
{
	m_MovingRight = false;
}

void Striker::moveUp()
{
	m_MovingUp = true;
}

void Striker::moveDown()
{
	m_MovingDown = true;
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
	if (m_MovingLeft && m_Position.x > 960 + 93) 
	{
		m_Position.x -= m_Speed * dt.asSeconds();
	}

	if (m_MovingRight && m_Position.x < 1827 - 38) 
	{
		m_Position.x += m_Speed * dt.asSeconds();
	}

	if (m_MovingUp && m_Position.y > 93 + 43)
	{
		m_Position.y -= m_Speed * dt.asSeconds();
	}

	if (m_MovingDown && m_Position.y < 987 - 43)
	{
		m_Position.y += m_Speed * dt.asSeconds();
	}

	m_Sprite.setOrigin(33, 33);
	m_Shape.setPosition(m_Position);

	//debug color delete when done make transparenet when done
	m_Shape.setFillColor(sf::Color::Green);
}

//93 to outer striker
//43 top and bottom of screen
//38 sides of screen