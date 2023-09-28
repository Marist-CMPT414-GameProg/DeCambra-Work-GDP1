#include "Striker.h"
#include "Puck.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

int main()
{
	// Low res code
	VideoMode vm(960, 540);

	// Low res code
	RenderWindow window(vm, "AirHockey");
	View view(sf::FloatRect(0, 0, 1920, 1080));
	window.setView(view);
	//End of low res code!! Everything else is the same!!

	int score = 0;
	int lives = 3;

	// Create a texture to hold a graphic on the GPU
	Texture textureBackground;

	// Load a graphic into the texture
	textureBackground.loadFromFile("graphics/background.png");

	// Create a sprite
	Sprite spriteBackground;

	// Attach the texture to the sprite
	spriteBackground.setTexture(textureBackground);

	// Set the spriteBackground to cover the screen
	spriteBackground.setScale(view.getSize().x / spriteBackground.getLocalBounds().width, view.getSize().y / spriteBackground.getLocalBounds().height);
	spriteBackground.setPosition(0, 0);

	// Create a striker texture
	Texture textureStriker;
	textureStriker.loadFromFile("graphics/striker_red.png");

	// Create a striker at the start position
	Striker striker(960 + 600, 540);
	striker.setShapeOrigin();
	striker.setTexture(textureStriker);	

	// Create a puck texture
	Texture texturePuck;
	texturePuck.loadFromFile("graphics/puck.png");

	// Create a puck
	Puck puck(960, 540);
	puck.setTexture(texturePuck);
	puck.setShapeOrigin();
	puck.setVelocity(0, 0);

	// Create a Text object called HUD
	Text hud;

	// A cool retro-style font
	Font font;
	font.loadFromFile("font/DS-DIGI.ttf");

	// Set the font to our retro-style
	hud.setFont(font);

	// Make it nice and big
	hud.setCharacterSize(75);

	// Choose a color
	hud.setFillColor(Color::Red);
	hud.setPosition(20, 20);

	// Here is our clock for timing everything
	Clock clock;

	while (window.isOpen())
	{
		/*
		Handle the player input
		*********************************************************************
		*********************************************************************
		*********************************************************************
		*/

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				// Quit the game when the window is closed
				window.close();
			}				
		}

		// Handle the player quitting
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		// Handle the pressing and releasing of the arrow keys
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			striker.moveLeft();
		}
		else
		{
			striker.stopLeft();
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			striker.moveRight();
		}
		else
		{
			striker.stopRight();
		}

		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			striker.moveUp();
		}
		else
		{
			striker.stopUp();
		}

		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			striker.moveDown();
		}
		else
		{
			striker.stopDown();
		}

		/*
		Update the striker, the puck and the HUD
		*********************************************************************
		*********************************************************************
		*********************************************************************
		*/

		// Update the delta time
		Time dt = clock.restart();
		striker.update(dt);
		puck.update(dt);

		// Update the HUD text
		std::stringstream ss;
		ss << "Score:" << score << "    Lives:" << lives;
		hud.setString(ss.str());

		// Set the position of the sprite to match the position of the striker
		striker.setSpritePosition(striker.getPosition().left, striker.getPosition().top);

		// Set the position of the sprite to match the position of the puck
		puck.setSpritePosition(puck.getPosition().left, puck.getPosition().top);

		// Get puck's x and y values
		float puckYPosition = puck.getYPosition();
		float puckXPosition = puck.getXPosition();

		// Handle the puck hitting the bottom or top
		if (puckYPosition <= 54.6 + 43 || puckYPosition >= 1025.4 - 43)
		{
			puck.reboundBottomOrTop();
		}

		// Handle puck hitting the sides
		if (puckYPosition > 673.4 || puckYPosition < 297.4)
		{
			if (puckXPosition <= 54.6 + 38 || puckXPosition >= 1865.4 - 38)
			{
				puck.reboundSides();
			}
		}
		// Handle puck being scored
		else if (puckXPosition < 0 || puckXPosition > 1920)
		{
			// striker.Goal();
			score++;

			// Reset players & puck
			striker.Goal(540, 1460);

			puck.setVelocity(0, 0);
			puck.Goal();
		}

		// Handle puck getting stuck in top and bottom edges of map
		if (puckYPosition < 96)
		{
			puck.setYPositionTop(striker);
		}
		else if (puckYPosition > 984)
		{
			puck.setYPositionBottom(striker);
		}

		// Handle puck getting stuck in left and right edges of map
		if (puckYPosition > 673.4 || puckYPosition < 297.4)
		{
			if (puckXPosition > 1828)
			{
				puck.setXPositionRight(striker);
			}
		}

		// Handle puck getting pushed outside of arena
		/*if (puckYPosition < 54.6 + 43)
		{
			puckYPosition = 54.6 + 43;
		}*/

		// Has the puck hit the striker?
		if (puck.getPosition().intersects(striker.getPosition()))
		{
			// Hit detected so reserve the puck and score a point
			puck.reboundStriker(striker);
		}		

		/*
		Draw the striker, the puck and the HUD
		*********************************************************************
		*********************************************************************
		*********************************************************************
		*/

		window.clear();

		window.draw(spriteBackground);
		window.draw(hud);

		window.draw(striker.getShape());
		window.draw(striker.getSprite());

		window.draw(puck.getShape());
		window.draw(puck.getSprite());

		window.display();
	}
	return 0;
}
