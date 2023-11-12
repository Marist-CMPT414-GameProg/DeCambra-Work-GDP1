#include "Flower.hpp"
#include "TextureHolder.hpp"

using namespace sf;

Flower::Flower(Vector2f const& position)
    : GameSprite("graphics/sunflower.png", position) {}
