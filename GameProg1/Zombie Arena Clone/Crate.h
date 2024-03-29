#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Crate
{
private:
    // Sprite that represents the obstacle
    Sprite m_Sprite;

    // The arena it exists in
    IntRect m_Arena;

    // Handle spawning
    bool m_Spawned;

public:
    Crate();

    // Prepare new obstacle
    void setArena(IntRect arena);
    
    void spawn();

    // Check position of obstacle
    FloatRect getPosition();

    // Get the sprite for drawing
    Sprite getSprite();

    // Is the obstacle spawned?
    bool isSpawned();
};