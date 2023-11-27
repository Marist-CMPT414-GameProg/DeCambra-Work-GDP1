#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "TileMap.h"

using namespace sf;

int main()
{
    Vector2i windowBorderOffset(11, 45);

    // create the window
    RenderWindow window(sf::VideoMode::getDesktopMode(), "Tilemap", sf::Style::Default);

    View mainView(FloatRect(-50, -50, 48 * 50, 28 * 50));
    window.setView(mainView);

    const int level1[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0, 1, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0, 1, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0, 1, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    sf::Texture beeTexture;
    beeTexture.loadFromFile("assets/sprites/bee.png");

    // create the tilemap from the level definition
    TileMap map;
    if (!map.load("assets/tilesets/tiles_sheet.png", sf::Vector2u(50, 50), level1, 46, 11))
        return -1;

    sf::RectangleShape boxie({ 75, 75 });
    boxie.setTexture(&beeTexture);
    boxie.setFillColor(sf::Color(255, 255, 0, 127));
    boxie.setOrigin(37.5, 37.5);
    boxie.setPosition(860, 320);


    std::cerr << "Detected " << map.intersects(boxie.getGlobalBounds()) << " collisions\n";

    sf::Shader shader;
    // Can this graphics card use shaders?
    if (sf::Shader::isAvailable()) {
        shader.loadFromFile("shaders/vertShader.vert", "shaders/rippleShader.frag");
        shader.setUniform("uTint", Glsl::Vec3(1, 0.5, 0.5));
    }
    else
    {
        window.close();
    }

    Clock clock;
    // run the main loop
    while (window.isOpen())
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)) {
                window.close();
            }
            if (event.type == sf::Event::MouseMoved) {
                boxie.setPosition(window.mapPixelToCoords(Mouse::getPosition() - window.getPosition() - windowBorderOffset));
            }
        }

        shader.setUniform("uTime", clock.getElapsedTime().asSeconds());

        // draw the map
        window.clear(sf::Color(128, 128, 128));
        window.draw(map);
        window.draw(boxie, &shader);
        window.display();
    }

    return 0;
}