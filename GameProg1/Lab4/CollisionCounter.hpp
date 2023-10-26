#ifndef HPP_HUD
#define HPP_HUD

#include <SFML/Graphics.hpp>
#include "Observer.hpp"

class CollisionCounter : public Observer
{
public:
    CollisionCounter(sf::Font const& font, sf::Vector2f const& pos);
    void draw(sf::RenderWindow& target) const;

    // Implement onNotify
    void onNotify(::Event const& ev) override;
private:
    sf::Text text;
    int count;
};

#endif HPP_HUD