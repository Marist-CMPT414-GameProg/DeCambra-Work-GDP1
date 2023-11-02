#include <array>
#include <iostream>
#include "Bee.h"
#include "Flower.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

int const MAX_GAME_OBJS = 10;
using GameObjArray = std::array<GameObject*, MAX_GAME_OBJS>;

int main()
{
    // Forward declarations
    void configureWindow(RenderWindow&);
    void populateScene(GameObjArray&);
    void handleInput(RenderWindow&, GameObjArray const&);
    void update(Clock&, GameObjArray const&);
    void render(RenderWindow&, GameObjArray const&);

    GameObjArray gameObjects;
    populateScene(gameObjects);

    RenderWindow window;
    configureWindow(window);

    // The main game loop
    Clock clock;
    while (window.isOpen())
    {
        handleInput(window, gameObjects);
        update(clock, gameObjects);
        render(window, gameObjects);
    }

    return 0;
}

// Handle input for the game loop
void handleInput(RenderWindow& window, GameObjArray const& gameObjects)
{
    Event event;
    while (window.pollEvent(event))
    {
        if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
        {
            window.close();
        }

        dynamic_cast<Bee*>(gameObjects[0])->handleInput(event);
    }
}

// Update the game incrementally by one frame
void update(Clock& clock, GameObjArray const& gameObjects)
{
    void checkCollisions(GameObjArray const&);

    Time dt = clock.restart();

    for (auto obj : gameObjects) 
    {
        if (obj) { obj->update(dt); }
    }

    checkCollisions(gameObjects);
}

// Draw the game world
void render(RenderWindow& window, GameObjArray const& gameObjects)
{
    window.clear();

    for (auto obj : gameObjects) 
    {
        if (obj) { obj->draw(window); }
    }

    window.display();
}

// Helper functions

void configureWindow(RenderWindow& window)
{
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    View mainView(sf::FloatRect(0, 0, 2160, 1440));
    window.create(VideoMode(resolution.x, resolution.y), "Collisions Demo", Style::Fullscreen);
    window.setView(mainView);
}

void populateScene(GameObjArray& gameObjects)
{
    for (int i = 1; i < gameObjects.size(); ++i)
    {
        gameObjects[i] = nullptr;
    }

    gameObjects[0] = new Bee(Vector2f(100, 100));
    gameObjects[1] = new Flower(Vector2f(400, 400));
    gameObjects[2] = new Flower(Vector2f(400, 1000));
    gameObjects[3] = new Flower(Vector2f(1000, 400));
    gameObjects[4] = new Flower(Vector2f(1000, 1000));
    gameObjects[5] = new Flower(Vector2f(1600, 400));
    gameObjects[6] = new Flower(Vector2f(1600, 1000));
}

void checkCollisions(GameObjArray const& gameObjects)
{
    Bee* bee = dynamic_cast<Bee*>(gameObjects[0]);

    FloatRect beeCollider = bee->getCollider();

    for (auto obj : gameObjects)
    {
        if (obj && obj != bee)
        {
            FloatRect objCollider = obj->getCollider();
            if (beeCollider.intersects(objCollider))
            {
                std::cerr << "Collision found!\n";
                bee->cancelMove();
            }
        }
    }
}