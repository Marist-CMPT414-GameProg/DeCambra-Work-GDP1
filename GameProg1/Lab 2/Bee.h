#ifndef HPP_BEE
#define HPP_BEE
#include <SFML/Graphics.hpp>

using namespace sf;

class Bee
{
private:
	Vector2f m_Position;

	Sprite m_Sprite;

	float m_Speed = 0.15f;
	
	float m_Angle = 0.0f;

	bool m_Active = true;

public:
	Bee(float startX, float startY);

	Sprite getSprite();

	float getAngle();

	float getSpeed();
	
	void setAngle(float newAngle);

	void setTexture(Texture const& texture)
	{
		m_Sprite.setTexture(texture);
	}

	void setPosition(float newX, float newY)
	{
		m_Sprite.setPosition(newX, newY);
	}

};

#endif HPP_BEE