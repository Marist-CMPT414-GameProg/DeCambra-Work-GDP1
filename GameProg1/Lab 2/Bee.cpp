#include "Bee.h"

// This is the constructor function
Bee::Bee(float startX, float startY)
{
	m_Position.x = startX;
	m_Position.y = startY;

	m_Sprite.setPosition(m_Position);

}

Sprite Bee::getSprite()
{
	return m_Sprite;
}

float Bee::getAngle()
{
	return m_Angle;
}

float Bee::getSpeed()
{
	return m_Speed;
}

void Bee::setAngle(float newAngle)
{
	m_Angle = newAngle;
}