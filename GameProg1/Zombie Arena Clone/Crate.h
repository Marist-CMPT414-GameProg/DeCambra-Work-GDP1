#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Crate
{
private:
    Vector2f m_Position;
    Sprite m_Sprite;
    Texture m_Texture;

public:
    Crate()
    {
        // Load the crate texture
        m_Texture.loadFromFile("graphics/crate.png");

        // Set the crate sprite's texture
        m_Sprite.setTexture(m_Texture);

        // Set the crate's position and size
        m_Sprite.setPosition(m_Position);
        m_Sprite.setScale(0.5f, 0.5f); // Adjust the scale as needed
    }

    // Add getter functions for the position and sprite
    Vector2f getPosition() const { return m_Position; }
    Sprite& getSprite() { return m_Sprite; }
    const Sprite& getSprite() const { return m_Sprite; }
};