#include "Planet.hpp"
#include "Event.hpp"


Planet::Planet(sf::Texture const& texture, sf::Vector2f const& pos)
    : sprite(texture)
{
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    sprite.setPosition(pos);
}

void Planet::draw(sf::RenderWindow& target) const
{
    target.draw(sprite);
}

void Planet::hit()
{
    Event ev(*this, "planet hit event");
    notify(ev);
}

sf::FloatRect const& Planet::getCollider() const
{
    return sprite.getGlobalBounds();
}