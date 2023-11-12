#ifndef HPP_GAMEOBJECT
#define HPP_GAMEOBJECT

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "Observer.hpp"
#include <array>

struct CollisionEvent;

/// <summary>
/// Simple abstract base class for game objects
/// </summary>
/// <remarks>
/// All game objects have a sprite and a simple collision rectangle. This
/// class also provides for object-specific game loop operations, such as
/// handling input, updating the object, and rendering the object.
/// </remarks>
class GameObject
    : public sf::Drawable
    , public Observer<CollisionEvent>
{
public:
    /// <summary>
    /// Gets the rectangular bounds for this 
    /// </summary>
    /// <returns></returns>
    virtual sf::FloatRect getCollider() const = 0;

    /// <summary>
    /// 
    /// </summary>
    /// <param name="collision"></param>
    virtual void onNotify(CollisionEvent const& collision);

    /// <summary>
    /// Allows for a game object to respond to user input.
    /// </summary>
    /// <remarks>
    /// Call this method in the game loop when handling input.
    /// </remarks>
    /// <param name="event">an input event</param>
    virtual void handleInput(sf::Event const&);

    /// <summary>
    /// Update the state of this object incrementally (i.e., one frame worth of update)
    /// </summary>
    /// <param name="dt">the elapsed time since the last frame</param>
    virtual void update(sf::Time const&);
};

class GameSprite : public GameObject
{
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::FloatRect getCollider() const override;
protected:
    GameSprite(std::string const&, sf::Vector2f const& position = sf::Vector2f());
    sf::Sprite sprite;
};

class GameBox : public GameObject
{
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::FloatRect getCollider() const override;
protected:
    GameBox(sf::Color const&, sf::Vector2f const&, sf::Vector2f const& = sf::Vector2f());
    sf::RectangleShape shape;
};

class GameOrb : public GameObject
{
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::FloatRect getCollider() const override;
protected:
    GameOrb(sf::Color const&, float, sf::Vector2f const& = sf::Vector2f());
    sf::CircleShape shape;
};

int const MAX_GAME_OBJS = 10;
using GameObjArray = std::array<GameObject*, MAX_GAME_OBJS>;

#endif HPP_GAMEOBJECT
