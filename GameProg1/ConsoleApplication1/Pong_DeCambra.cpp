#include "Striker.h"
#include "Puck.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main()
{
	// Low res code
	VideoMode vm(960, 540);

	// Low res code
	RenderWindow window(vm, "AirHockey");
	View view(sf::FloatRect(0, 0, 1920, 1080));
	window.setView(view);
	//End of low res code!! Everything else is the same!!

	int score1 = 0;
	int score2 = 0;

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

	// Create a striker (player 1) texture
	Texture textureStriker1;
	textureStriker1.loadFromFile("graphics/striker_blue.png");

	// Create a striker at the start position (player 1)
	Striker striker1(960 - 500, 540);
	striker1.setShapeOrigin();
	striker1.setTexture(textureStriker1);

	// Create a striker (player 2) texture
	Texture textureStriker2;
	textureStriker2.loadFromFile("graphics/striker_red.png");

	// Create a striker at the start position (player 2)
	Striker striker2(960 + 500, 540);
	striker2.setShapeOrigin();
	striker2.setTexture(textureStriker2);	

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
	hud.setCharacterSize(60);

	// Choose a color
	hud.setFillColor(Color::Red);
	hud.setPosition(868, -16.5);

	// Title screen
	Text title;
	title.setFont(font);
	title.setCharacterSize(200);
	title.setFillColor(Color::Black);
	title.setPosition(500, 200);

	// Blue wins
	Text blueWin;
	blueWin.setFont(font);
	blueWin.setCharacterSize(200);
	blueWin.setFillColor(Color::Transparent);
	blueWin.setPosition(450, 200);

	// Red wins
	Text redWin;
	redWin.setFont(font);
	redWin.setCharacterSize(200);
	redWin.setFillColor(Color::Transparent);
	redWin.setPosition(540, 200);

	// Here is our clock for timing everything
	Clock clock;

	// Check if game is paused bool
	bool paused = true;

	// Audio
	SoundBuffer puckHitBuffer;
	puckHitBuffer.loadFromFile("audio/puck_hit.wav");
	Sound puckHit;
	puckHit.setBuffer(puckHitBuffer);

	SoundBuffer scoreBuffer;
	scoreBuffer.loadFromFile("audio/score.wav");
	Sound score;
	score.setBuffer(scoreBuffer);

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

		Time dt = clock.restart();
		// Handle the player quitting
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			paused = false;
			title.setFillColor(Color::Transparent);
			redWin.setFillColor(Color::Transparent);
			blueWin.setFillColor(Color::Transparent);
			score1 = 0;
			score2 = 0;

			// Reset the players & puck
			striker1.Goal(540, 960 - 500);
			striker2.Goal(540, 960 + 500);

			puck.setVelocity(0, 0);
			puck.Goal();
		}

		// Set the position of the sprite to match the position of the striker1
		striker1.setSpritePosition(striker1.getPosition().left, striker1.getPosition().top);

		// Set the position of the sprite to match the position of the striker2
		striker2.setSpritePosition(striker2.getPosition().left, striker2.getPosition().top);

		// Set the position of the sprite to match the position of the puck
		puck.setSpritePosition(puck.getPosition().left, puck.getPosition().top);

		std::stringstream titless;
		titless <<  "air hockey!";
		title.setString(titless.str());

		std::stringstream redWins;
		redWins << "RED	 WINS!";
		redWin.setString(redWins.str());

		std::stringstream blueWins;
		blueWins << "BLUE	 WINS!";
		blueWin.setString(blueWins.str());


		/*
		IF NOT PAUSED
		*********************************************************************
		*********************************************************************
		*********************************************************************
		*/

		if (!paused)
		{
			/*
			PLAYER 1 INPUT
			*********************************************************************
			*********************************************************************
			*********************************************************************
			*/

			// Handle the pressing and releasing of the arrow keys
			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				// If puck is not at the left side of the screen set striker max distance to edge of screen
				if (puck.getXPosition() > 94)
				{
					striker1.moveLeft(dt, 40 + 93);
				}
				// If puck is at left side of screen and striker is colliding wiht puck set max distance to not collide with puck
				else if (puck.getXPosition() < 102 && puck.getPosition().intersects(striker1.getPosition()))
				{
					striker1.moveRight(dt, 241.6);
				}
			}
			else
			{
				striker1.stopLeft();
			}

			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				// Check if both strikers are colliding
				if (puck.getXPosition() <= 905 && puck.getPosition().intersects(striker1.getPosition()) && striker2.getXPosition() >= 1201)
				{
					striker1.moveRight(dt, 960 - 93 - 55 - 93);
				}
				else
				{
					striker1.moveRight(dt, 960 - 93);
				}
			}
			else
			{
				striker1.stopRight();
			}

			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				// If puck is not at the top of the screen set striker max distance to edge of screen
				if (puck.getYPosition() > 102)
				{
					striker1.moveUp(dt, 93 + 46);
				}
				// If puck is at top of screen and striker is colliding wiht puck set max distance to not collide with puck
				else if (puck.getYPosition() < 110 && puck.getPosition().intersects(striker1.getPosition()))
				{
					striker1.moveUp(dt, 283.6);
				}
			}
			else
			{
				striker1.stopUp();
			}

			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				// If puck is not at the bottom of the screen set striker max distance to edge of screen
				if (puck.getYPosition() < 983)
				{
					puck.notColliding();
					striker1.moveDown(dt, 987 - 43);
				}
				// If puck is at bottom of screen and striker is colliding wiht puck set max distance to not collide with puck
				else if (puck.getYPosition() > 975 && puck.getPosition().intersects(striker1.getPosition()))
				{
					puck.isColliding();
					striker1.moveDown(dt, 796.4);
				}
			}
			else
			{
				striker1.stopDown();
			}

			/*
			PLAYER 2 INPUT
			*********************************************************************
			*********************************************************************
			*********************************************************************
			*/

			// Handle the pressing and releasing of the arrow keys
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				// Check if both strikers are colliding
				if (puck.getXPosition() >= 1015 && striker1.getXPosition() <= 719 && puck.getPosition().intersects(striker2.getPosition()))
				{
					striker2.moveLeft(dt, 960 + 93 + 55 + 93);
				}
				else
				{
					striker2.moveLeft(dt, 960 + 93);
				}
				
			}
			else
			{
				striker2.stopLeft();
			}

			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				// If puck is not at the right side of the screen set striker max distance to edge of screen
				if (puck.getXPosition() < 1816)
				{
					striker2.moveRight(dt, 1780);
				}
				// If puck is at right side of screen and striker is colliding wiht puck set max distance to not collide with puck
				else if (puck.getXPosition() > 1804 && puck.getPosition().intersects(striker2.getPosition()))
				{
					striker2.moveRight(dt, 1630);
				}
			}
			else
			{
				striker2.stopRight();
			}

			if (Keyboard::isKeyPressed(Keyboard::Up))
			{
				// If puck is not at the top of the screen set striker max distance to edge of screen
				if (puck.getYPosition() > 102)
				{
					striker2.moveUp(dt, 93 + 46);
				}
				// If puck is at top of screen and striker is colliding wiht puck set max distance to not collide with puck
				else if (puck.getYPosition() < 110 && puck.getPosition().intersects(striker2.getPosition()))
				{
					striker2.moveUp(dt, 283.6);
				}
			}
			else
			{
				striker2.stopUp();
			}

			if (Keyboard::isKeyPressed(Keyboard::Down))
			{
				// If puck is not at the bottom of the screen set striker max distance to edge of screen
				if (puck.getYPosition() < 983)
				{
					puck.notColliding();
					striker2.moveDown(dt, 987 - 43);
				}
				// If puck is at bottom of screen and striker is colliding wiht puck set max distance to not collide with puck
				else if (puck.getYPosition() > 975 && puck.getPosition().intersects(striker2.getPosition()))
				{
					puck.isColliding();
					striker2.moveDown(dt, 796.4);
				}
			}
			else
			{
				striker2.stopDown();
			}


			/*
			Update the striker, the puck and the HUD
			*********************************************************************
			*********************************************************************
			*********************************************************************
			*/

			// Update the delta time

			striker1.update(dt);
			striker2.update(dt);
			puck.update(dt);

			// Update the HUD text
			std::stringstream ss;
			ss << score1 << "	:	" << score2;
			hud.setString(ss.str());

			// Set the position of the sprite to match the position of the striker1
			striker1.setSpritePosition(striker1.getPosition().left, striker1.getPosition().top);

			// Set the position of the sprite to match the position of the striker2
			striker2.setSpritePosition(striker2.getPosition().left, striker2.getPosition().top);

			// Set the position of the sprite to match the position of the puck
			puck.setSpritePosition(puck.getPosition().left, puck.getPosition().top);

			// Handle the puck hitting the bottom or top
			if (puck.getYPosition() <= 102 || puck.getYPosition() >= 983)
			{
				puck.reboundBottomOrTop();

				// Play hit sfx
				puckHit.play();
			}

			// Handle the puck hitting the sides
			if (puck.getYPosition() > 645 || puck.getYPosition() < 385)
			{
				if (puck.getXPosition() < 94 || puck.getXPosition() > 1816)
				{
					puck.reboundSides();

					// Play hit sfx
					puckHit.play();
				}
			}
			// Handle the puck being scored
			else if (puck.getXPosition() < 0 || puck.getXPosition() > 1920)
			{
				if (puck.getXPosition() > 0)
				{
					score1++;

					// Play score sfx
					score.play();
				}
				else
				{
					score2++;

					// Play score sfx
					score.play();
				}

				// Reset the players & puck
				striker1.Goal(540, 960 - 500);
				striker2.Goal(540, 960 + 500);

				puck.setVelocity(0, 0);
				puck.Goal();

				if (score1 == 5)
				{
					blueWin.setFillColor(Color::Blue);
					puck.Goal();
					striker1.Goal(540, 960 - 500);
					striker2.Goal(540, 960 + 500);
					paused = true;
				}
				else if (score2 == 5)
				{
					redWin.setFillColor(Color::Red);
					puck.Goal();
					striker1.Goal(540, 960 - 500);
					striker2.Goal(540, 960 + 500);
					paused = true;
				}
			}

			// Handle the puck through the edges of map
			if (puck.getYPosition() < 102)
			{
				puck.setYPositionTop();
			}
			else if (puck.getYPosition() > 984)
			{
				puck.setYPositionBottom();
			}

			// Handle puck getting stuck in left and right edges of map
			if (puck.getYPosition() > 645 || puck.getYPosition() < 385)
			{
				if (puck.getXPosition() > 1816)
				{
					puck.setXPositionRight();
				}

				if (puck.getXPosition() < 94)
				{
					puck.setXPositionLeft();
				}
			}

			// Has the puck hit the striker?
			if (puck.getPosition().intersects(striker1.getPosition()))
			{
				// Hit detected so reserve the puck and score a point
				puck.reboundStriker(striker1);

				// Play hit sfx
				puckHit.play();
			}

			// Has the puck hit the striker?
			if (puck.getPosition().intersects(striker2.getPosition()))
			{
				// Hit detected so reserve the puck and score a point
				puck.reboundStriker(striker2);

				// Play hit sfx
				puckHit.play();
			}
		}		
		std::stringstream ss;
		ss << score1 << "	:	" << score2;
		hud.setString(ss.str());

		/*
		Draw the striker, the puck and the HUD
		*********************************************************************
		*********************************************************************
		*********************************************************************
		*/

		window.clear();

		window.draw(spriteBackground);
		window.draw(hud);
		window.draw(title);
		window.draw(redWin);
		window.draw(blueWin);

		window.draw(striker1.getShape());
		window.draw(striker1.getSprite());

		window.draw(striker2.getShape());
		window.draw(striker2.getSprite());

		window.draw(puck.getShape());
		window.draw(puck.getSprite());

		window.display();
	}
	return 0;
}
