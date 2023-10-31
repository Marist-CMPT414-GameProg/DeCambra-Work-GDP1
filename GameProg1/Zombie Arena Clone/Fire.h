#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Fire
{
private:
    // Start value
    const int FIRE_START_VALUE = 5;

    // Sprite that represents the obstacle
    Sprite m_Sprite;

    // The arena it exists in
    IntRect m_Arena;

    // How much damage the fire does
    int m_Damage;

    // Handle spawning
    bool m_Spawned;

public:
    Fire();

    // Prepare new obstacle
    void setArena(IntRect arena);

    void spawn();

    // Check position of obstacle
    FloatRect getPosition();

    // Get the sprite for drawing
    Sprite getSprite();

    // Is the obstacle spawned?
    bool isSpawned();

    // Has the player or fire hit the fire
    int burnDamage();
};