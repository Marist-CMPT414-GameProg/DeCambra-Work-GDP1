#include "Crate.h"
#include "TextureHolder.h"


Crate::Crate()
{
    m_Sprite = Sprite(TextureHolder::GetTexture("graphics/crate.png"));
    m_Sprite.setOrigin(25, 25);
}

void Crate::setArena(IntRect arena)
{
    // Copy the details of the arena to the pickup's m_Arena
    m_Arena.left = arena.left + 100;
    m_Arena.width = arena.width - 100;
    m_Arena.top = arena.top + 100;
    m_Arena.height = arena.height - 100;

    spawn();
}

void Crate::spawn()
{
    // Spawn at a random location
    int x = (rand() % m_Arena.width);
    int y = (rand() % m_Arena.height);

    m_Spawned = true;

    m_Sprite.setPosition(x, y);
}

FloatRect Crate::getPosition()
{
    return m_Sprite.getGlobalBounds();
}

Sprite Crate::getSprite()
{
    return m_Sprite;
}

bool Crate::isSpawned()
{
    return m_Spawned;
}