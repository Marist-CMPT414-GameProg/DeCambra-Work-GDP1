#include "Puck.h"
#include "Striker.h"
#include <iostream>
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

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

void Puck::isColliding()
{
	m_Colliding = true;
}

void Puck::notColliding()
{
	m_Colliding = false;
}

void Puck::setVelocity(float x, float y)
{
	m_InitialVelocity = sf::Vector2f(x, y);
	m_DirectionX = x;
	m_DirectionY = y;	
}

void Puck::setYPositionTop()
{
	m_Position.y = 102;
}

void Puck::setYPositionBottom()
{
	m_Position.y = 983;
}

void Puck::setXPositionRight()
{
	m_Position.x = 1816;
}

void Puck::setXPositionLeft()
{
	m_Position.x = 94;
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
	// Calculate the angle between the puck and the striker
	float angle = std::atan2(m_Position.y - striker.getYPosition(), m_Position.x - striker.getXPosition());

	// Convert the angle from radians to degrees
	float angleDegrees = angle * (180.0 / M_PI);

	// Now angleDegrees contains the angle between the puck and the striker
	std::cout << "Angle between puck and striker: " << angleDegrees << " degrees" << std::endl;


	// Calculate the current speed of the puck
	float currentSpeed = std::sqrt(m_DirectionX * m_DirectionX + m_DirectionY * m_DirectionY);

	if (striker.getXVelocity() != 0 || striker.getYVelocity() != 0)
	{
		// Calculate the new velocity components based on the angle and default speed
		float newVelocityX = std::cos(angle) * m_Speed;
		float newVelocityY = std::sin(angle) * m_Speed;

		// Set the velocity of the puck
		setVelocity(newVelocityX, newVelocityY);
	}
	else
	{
		// Calculate the new velocity components based on the angle and default speed
		float newVelocityX = std::cos(angle) * currentSpeed;
		float newVelocityY = std::sin(angle) * currentSpeed;

		// Set the velocity of the puck
		setVelocity(newVelocityX, newVelocityY);
	}
	
}

void Puck::Goal()
{
	m_Position.x = 960;
	m_Position.y = 540;
}

void Puck::update(Time dt)
{
	// Introduce drag to slow down the puck
	const float dragFactor = 0.9997f;
	m_DirectionX *= dragFactor;
	m_DirectionY *= dragFactor;

	// Update the puck position variables
	m_Position.y += m_DirectionY * m_Speed * dt.asSeconds();
	m_Position.x += m_DirectionX * m_Speed * dt.asSeconds();

	// Move the puck
	m_Shape.setPosition(m_Position);

	m_Shape.setPosition(m_Position);
	m_Shape.setFillColor(sf::Color::Transparent);
}