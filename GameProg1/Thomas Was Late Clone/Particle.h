#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Particle
{
private:
	Vector2f m_Position;
	Vector2f m_Velocity;
	Color m_Color;

public:
	Particle(Vector2f direction, Color color);

	void update(float dt);

	void setPosition(Vector2f position);

	Vector2f getPosition();

	Color getColor();
};