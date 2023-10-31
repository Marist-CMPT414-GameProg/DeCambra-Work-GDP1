#include "Fire.h"
#include "TextureHolder.h"

Fire::Fire()
{
	m_Sprite = Sprite(TextureHolder::GetTexture("graphics/fire.png"));

	m_Damage = FIRE_START_VALUE;

	m_Sprite.setOrigin(25, 25);
}

void Fire::setArena(IntRect arena)
{
    // Copy the details of the arena to the pickup's m_Arena
    m_Arena.left = arena.left + 100;
    m_Arena.width = arena.width - 100;
    m_Arena.top = arena.top + 100;
    m_Arena.height = arena.height - 100;

    spawn();
}

void Fire::spawn()
{
    // Spawn at a random location
    int x = (rand() % m_Arena.width);
    int y = (rand() % m_Arena.height);

    m_Spawned = true;

    m_Sprite.setPosition(x, y);
}

FloatRect Fire::getPosition()
{
    return m_Sprite.getGlobalBounds();
}

Sprite Fire::getSprite()
{
    return m_Sprite;
}

bool Fire::isSpawned()
{
    return m_Spawned;
}

int Fire::burnDamage()
{
    return m_Damage;
}