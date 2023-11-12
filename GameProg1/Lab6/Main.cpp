#include <array>
#include <iostream>
#include <typeinfo>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
#include "Bee.hpp"
#include "Player.hpp"
#include "Flower.hpp"
#include "Trigger.hpp"
#include "SimplePhysics.hpp"

using namespace sf;
using namespace std;

int main()
{
    // Forward declarations
    void configureWindow(RenderWindow&);
    void populateScene(GameObjArray&);
    void handleInput(RenderWindow&, GameObjArray const&);
    void update(Clock&, GameObjArray const&);
    void render(RenderWindow&, GameObjArray const&);

    // Variable initializations
    GameObjArray gameObjects;
    populateScene(gameObjects);

    RenderWindow window;
    configureWindow(window);

    // Game loop
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
        if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
            window.close();
        }

        for (auto obj : gameObjects) {
            if (obj) { obj->handleInput(event); }
        }
    }
}

// Update the game incrementally by one frame
void update(Clock& clock, GameObjArray const& gameObjects)
{
    Time dt = clock.restart();
    float dtAsSeconds = dt.asSeconds();

    for (auto obj : gameObjects) {
        if (obj) { obj->update(dt); }
    }

    Physics::checkCollisions(gameObjects);
}

// Draw the game world
void render(RenderWindow& window, GameObjArray const& gameObjects)
{
    window.clear();

    for (auto obj : gameObjects) {
        if (obj) { window.draw(*obj); }
    }

    window.display();
}

// Helper functions

void configureWindow(RenderWindow& window)
{
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width * 0.75f;
    resolution.y = VideoMode::getDesktopMode().height * 0.75f;

    View mainView(sf::FloatRect(0, 0, 2160, 1440));
    window.create(VideoMode(resolution.x, resolution.y), "Collisions Demo", Style::Default);
    window.setView(mainView);
}

void populateScene(GameObjArray& gameObjects)
{
    gameObjects.fill(nullptr);
    gameObjects[0] = new Player(Vector2f(400, 700));
    gameObjects[1] = new Flower(Vector2f(1280, 720));

    Trigger* button1 = new Trigger(Color::Red, Vector2f(200, 200));
    gameObjects[2] = button1;

    Trigger* button2 = new Trigger(Color::Green, Vector2f(200, 700));
    gameObjects[3] = button2;

    Trigger* button3 = new Trigger(Color::Blue, Vector2f(200, 1200));
    gameObjects[4] = button3;

    Bee* bee = new Bee(Vector2f(1280, 720), Vector2f(1800, 400));
    gameObjects[5] = bee;

    button1->addObserver(*bee);
    button2->addObserver(*bee);
    button3->addObserver(*bee);
}
