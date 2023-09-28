#include "Puck.h"
#include "Striker.h"

// This the constructor function
Puck::Puck(float startX, float startY)
{
	m_Position.x = startX;
	m_Position.y = startY;

	m_Shape.setRadius(54.6);
	m_Shape.setPosition(m_Position);
}

FloatRect Puck::getPosition()
{
	return m_Shape.getGlobalBounds();
}

CircleShape Puck::getShape()
{
	return m_Shape;
}

Sprite Puck::getSprite()
{
	return m_Sprite;
}

float Puck::getXVelocity()
{
	return m_DirectionX;
}

float Puck::getYPosition()
{
	return m_Position.y;
}

float Puck::getXPosition()
{
	return m_Position.x;
}

void Puck::setVelocity(float x, float y)
{
	m_DirectionX = x;
	m_DirectionY = y;
	m_InitialVelocity = sf::Vector2f(x, y);
}

void Puck::reboundSides()
{
	m_DirectionX = -m_DirectionX;
}

void Puck::reboundBottomOrTop()
{
	m_DirectionY = -m_DirectionY;
}

void Puck::reboundStriker(Striker& striker)
{
	// Inherit velocity from the striker
	setVelocity(striker.getXVelocity(), striker.getYVelocity());
}

void Puck::Goal()
{
	m_Position.y = 960;
	m_Position.x = 540;
}

void Puck::update(Time dt)
{
	// Introduce drag to slow down the puck
	const float dragFactor = 0.99999f;
	m_DirectionX *= dragFactor;
	m_DirectionY *= dragFactor;

	// Update the puck position variables
	m_Position.y += m_DirectionY * m_Speed * dt.asSeconds();
	m_Position.x += m_DirectionX * m_Speed * dt.asSeconds();

	// Move the puck and the bat
	// m_Sprite.setPosition(m_Position);
	m_Shape.setPosition(m_Position);

	//debug color delete when done make transparenet when done
	m_Shape.setFillColor(sf::Color::Green);
}