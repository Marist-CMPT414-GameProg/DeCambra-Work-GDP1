#include "GameObject.hpp"
#include "TextureHolder.hpp"

using namespace sf;

/* Game Object base class*/

void
GameObject::handleInput(Event const&) {}

void
GameObject::update(Time const&) {}

void GameObject::onNotify(CollisionEvent const& collision) {}

/* Sprite-based Game Objects */

GameSprite::GameSprite(std::string const& textureFilename, Vector2f const& position)
    : sprite(TextureHolder::GetTexture(textureFilename))
{
    sprite.setOrigin(0.5f * getCollider().getSize());
    sprite.setPosition(position);
}

FloatRect
GameSprite::getCollider() const
{
    return sprite.getGlobalBounds();
}

void GameSprite::draw(RenderTarget& target, RenderStates states) const
{
    target.draw(sprite, states);
}

/* Shape-based Game Objects */

GameBox::GameBox(Color const& color, Vector2f const& size, Vector2f const& position)
    : shape(size)
{
    shape.setOrigin(0.5f * getCollider().getSize());
    shape.setPosition(position);
}

FloatRect
GameBox::getCollider() const
{
    return shape.getGlobalBounds();
}

void GameBox::draw(RenderTarget& target, RenderStates states) const
{
    target.draw(shape, states);
}

GameOrb::GameOrb(Color const& color, float radius, Vector2f const& position)
    : shape(radius)
{
    shape.setOrigin(0.5f * getCollider().getSize());
    shape.setPosition(position);
    shape.setFillColor(color);
}

FloatRect
GameOrb::getCollider() const
{
    return shape.getGlobalBounds();
}

void GameOrb::draw(RenderTarget& target, RenderStates states) const
{
    target.draw(shape, states);
}
