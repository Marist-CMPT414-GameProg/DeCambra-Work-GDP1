#ifndef CPP_HELLO
#define CPP_HELLO

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

int main()
{
    cout << "Hello, World!" << endl;

    RenderWindow window({ 500, 250 }, "Lab 1", Style::Default);

    Font font;
    if (!font.loadFromFile("../../SFML-2.6.0/examples/opengl/resources/tuffy.ttf"))
    {
        return 1;
    }        

    Text text("Hello World!", font, 75);
    text.setPosition(75, 75);

    // Create a text "timer" on screen to count down to zero
    Text timer("10", font, 50);
    timer.setPosition(220, 170);

    float secsRemaining = 5;
    Clock clock;
    clock.restart();

    while (secsRemaining > 0 && window.isOpen())
    {
        // Get and Process Input
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        // Update the scene
        float dt = clock.getElapsedTime().asSeconds();
        clock.restart();

        secsRemaining -= dt;
        timer.setString(to_string((int)secsRemaining));

        // Render the scene
        window.clear();
        window.draw(text);
        window.draw(timer);
        window.display();        
    }

    return 0;
}
#endif CPP_HELLO