#ifndef HPP_FLOWER
#define HPP_FLOWER

#include "GameObject.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

/// <summary>
/// Simple static obstacle in the form of a flower.
/// </summary>
class Flower : public GameSprite
{
public:
    /// <summary>
    /// Creates a new flower obstacle at the specified position.
    /// </summary>
    /// <param name="position">desired location of the flower (in global coordinates)</param>
    Flower(sf::Vector2f const&);
};

#endif HPP_FLOWER
