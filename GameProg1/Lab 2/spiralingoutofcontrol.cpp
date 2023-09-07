#include <SFML/Graphics.hpp>
#include <cmath>

using namespace sf;

// Define an enum class for Direction
enum class Direction
{
    Clockwise,
    CounterClockwise
};

int main()
{
    // Create a video mode object
    VideoMode vm(500, 500);

    // Create and open a window for the game
    RenderWindow window(vm, "SpiralingOutOfControl", Style::Default);

    // Create a texture to hold a graphic on the GPU
    Texture textureBackground;

    // Load a graphic into the texture
    textureBackground.loadFromFile("graphics/grass.png");

    // Create a sprite
    Sprite spriteBackground;

    // Attach the texture to the sprite
    spriteBackground.setTexture(textureBackground);

    // Set the spriteBackground to cover the screen
    spriteBackground.setPosition(0, 0);

    // Create a view that matches the background size (1024x1024)
    View view(FloatRect(0, 0, 1024, 1024));
    window.setView(view);

    // Make a Sunflower sprite
    Texture textureFlower;
    textureFlower.loadFromFile("graphics/sunflower.png");
    Sprite spriteFlower;
    spriteFlower.setTexture(textureFlower);
    spriteFlower.setPosition(250, 250);

    // Set up the bee
    Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");
    Sprite spriteBee;
    spriteBee.setTexture(textureBee);

    // Initialize the direction as clockwise
    Direction beeDirection = Direction::Clockwise;

    // Is the bee currently moving?
    bool beeActive = true;

    // How fast can the bee fly?
    float beeSpeed = 1.25f;

    // Bee animation variables
    float angle = 0.0f; 

    // Set the initial position of the bee based on the initial angle
    float initialX = 400 + cos(angle) * 250; 
    float initialY = 400 + sin(angle) * 250; 
    spriteBee.setPosition(initialX, initialY);

    while (window.isOpen())
    {
        // Handle events
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space)
            {
                // Toggle the direction of the bee's movement
                if (beeDirection == Direction::Clockwise)
                {
                    beeDirection = Direction::CounterClockwise;
                }
                else
                {
                    beeDirection = Direction::Clockwise;
                }
            }
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
            {
                window.close();
            }
        }

        // Update bee position for circular motion
        if (beeActive)
        {
            // Calculate new position based on the direction
            if (beeDirection == Direction::Clockwise)
            {
                angle += 0.005f * beeSpeed;
            }
            else
            {
                angle -= 0.005f * beeSpeed;
            }

            // Calculate new position in a circle
            float x = 400 + cos(angle) * 250;
            float y = 400 + sin(angle) * 250;

            spriteBee.setPosition(x, y);

            if (angle >= 2 * 3.14159265f)
            {
                angle = 0.0f;
            }
        }

        // Clear and draw
        window.clear();
        window.draw(spriteBackground);
        window.draw(spriteFlower);
        window.draw(spriteBee);
        window.display();
    }

    return 0;
}
