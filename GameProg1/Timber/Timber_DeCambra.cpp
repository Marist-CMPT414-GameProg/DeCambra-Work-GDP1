// Include important C++ libraries here
#include <sstream>
#include <SFML/Graphics.hpp>

// Make code easier to type with "using namespace"
using namespace sf;

// Function declaration
void updateBranches(int seed);

const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];

// Where is player/branhc?
// Left or right
enum class side {LEFT, RIGHT, NONE};
side branchPositions[NUM_BRANCHES];

int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);

	// Create and open a window for the game
	RenderWindow window(vm, "Timber!!!", Style::Fullscreen);

	// Create a texture to hold a graphic on the GPU
	Texture textureBackground;

	// Load a graphic into the texture
	textureBackground.loadFromFile("graphics/background.png");

	// Create a sprite
	Sprite spriteBackground;

	// Attach the texture to the sprite
	spriteBackground.setTexture(textureBackground);

	// Set the spriteBackground to cover the screen
	spriteBackground.setPosition(0, 0);

	// Make a tree sprite
	Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");
	Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(810, 0);

	// Prepare the bee
	Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");
	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(0, 800);

	// Is the bee currently moving?
	bool beeActive = false;

	// How fast can the bee fly?
	float beeSpeed = 25.0f;

	// Make 3 ships sprites
	Texture textureShip1;
	Texture textureShip2;
	Texture textureShip3;

	// Load 3 new textures
	textureShip1.loadFromFile("graphics/ship1.png");
	textureShip2.loadFromFile("graphics/ship2.png");
	textureShip3.loadFromFile("graphics/ship3.png");

	// 3 New sprites
	Sprite spriteShip1;
	Sprite spriteShip2;
	Sprite spriteShip3;
	spriteShip1.setTexture(textureShip1);
	spriteShip2.setTexture(textureShip2);
	spriteShip3.setTexture(textureShip3);

	// Position the ships on the left of the screen & at different heights
	spriteShip1.setPosition(0, 0);
	spriteShip2.setPosition(0, 250);
	spriteShip3.setPosition(0, 500);

	// Are the ships currently on screen?
	bool ship1Active = false;
	bool ship2Active = false;
	bool ship3Active = false;

	// How fast is each ship?
	float ship1Speed = 100.0f;
	float ship2Speed = 100.0f;
	float ship3Speed = 100.0f;

	// Define minimum and maximum scaling factors for the ships
	const float minScale = 0.25f;
	const float maxScale = 1.0f;

	// Initialize random scales for each ship
	float ship1Scale = minScale + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxScale - minScale)));
	float ship2Scale = minScale + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxScale - minScale)));
	float ship3Scale = minScale + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxScale - minScale)));

	// Variables to control time itself
	Clock clock;

	// Time bar
	RectangleShape timeBar;
	float timeBarStartWidth = 400;
	float timeBarHeight = 80;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

	Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

	// Track whether the game is running
	bool paused = true;

	// Draw some text
	int score = 0;

	sf::Text messageText;
	sf::Text scoreText;

	// We need to choose a font
	sf::Font font;
	font.loadFromFile("fonts/Starjedi.ttf");

	// Set the font to our message
	messageText.setFont(font);
	scoreText.setFont(font);

	// Assign the actual message
	messageText.setString("Press Enter to start!");
	scoreText.setString("Score: 0");

	// Make it really big
	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);

	// Choose a color
	messageText.setFillColor(Color::White);
	scoreText.setFillColor(Color::White);

	// Position the text
	FloatRect textRect = messageText.getLocalBounds();

	messageText.setOrigin(textRect.left +
		textRect.width / 2.0f,
		textRect.top +
		textRect.height / 2.0f);

	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

	scoreText.setPosition(20, 20);

	// Prepare 5 branches
	Texture textureBranch;
	textureBranch.loadFromFile("graphics/branch.png");

	// Set the texture for each branch sprite
	for (int i = 0; i < NUM_BRANCHES; i++)
	{
		branches[i].setTexture(textureBranch);
		branches[i].setPosition(-2000, -2000);

		// Set the sprite's origin to dead center
		// We can then spin it round without changing its position
		branches[i].setOrigin(220, 20);
	}

	updateBranches(1);
	updateBranches(2);
	updateBranches(3);
	updateBranches(4);
	updateBranches(5);

	while (window.isOpen())
	{
		// Score ++;

		/*
		****************************************
		Handle the players input
		****************************************
		*/

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		// Start the game
		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			paused = false;

			// Reset the time and score
			score = 0;
			timeRemaining = 5;
		}

		/*
		****************************************
		Update the scene
		****************************************
		*/

		if (!paused)
		{
			// Measure time
			Time dt = clock.restart();

			// Subtract from the amount of time remaining
			timeRemaining -= dt.asSeconds();

			// size up the time bar
			timeBar.setSize(Vector2f(timeBarWidthPerSecond *
				timeRemaining, timeBarHeight));


			if (timeRemaining <= 0.0f)
			{

				// Pause the game
				paused = true;

				// Change the message shown to the player
				messageText.setString("out of time!!");

				//Reposition the text based on its new size
				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left +
					textRect.width / 2.0f,
					textRect.top +
					textRect.height / 2.0f);

				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
			}


			// Set the bee
			if (!beeActive)
			{
				// How fast is the bee
				srand((int)time(0));
				beeSpeed = (rand() % 200) + 200;

				// How high is the bee
				srand((int)time(0) * 10);
				float height = (rand() % 500) + 500;
				spriteBee.setPosition(2000, height);
				beeActive = true;
			}
			else
				// Move the bee
			{
				spriteBee.setPosition(spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()), spriteBee.getPosition().y);

				// Has the bee reached the left-hand edge of the screen?
				if (spriteBee.getPosition().x < -100)
				{
					// Set it up ready to be a whole new bee next frame
					beeActive = false;
				}
			}

			// Manage the ships
			// Ship 1
			if (!ship1Active)
			{
				// How fast is the ship
				srand((int)time(0) * 10);
				ship1Speed = (rand() % 200);

				// How high is the ship
				srand((int)time(0) * 10);
				float height = (rand() % 150);
				spriteShip1.setPosition(-200, height);
				ship1Active = true;

				// Generate random scale factor between minScale and maxScale
				ship1Scale = minScale + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxScale - minScale)));

				// Update ship's scale
				spriteShip1.setScale(ship1Scale, ship1Scale);
			}
			else
			{

				spriteShip1.setPosition(spriteShip1.getPosition().x + (ship1Speed * dt.asSeconds()), spriteShip1.getPosition().y);

				// Has the ship reached the right hand edge of the screen?
				if (spriteShip1.getPosition().x > 1920)
				{
					// Set it up ready to be a whole new ship next frame
					ship1Active = false;
				}
			}

			// ship 2
			if (!ship2Active)
			{

				// How fast is the ship
				srand((int)time(0) * 20);
				ship2Speed = (rand() % 200);

				// How high is the ship
				srand((int)time(0) * 20);
				float height = (rand() % 300) - 150;
				spriteShip2.setPosition(-200, height);
				ship2Active = true;

				// Generate random scale factor between minScale and maxScale
				ship2Scale = minScale + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxScale - minScale)));

				// Update ship's scale
				spriteShip2.setScale(ship1Scale, ship1Scale);
			}
			else
			{

				spriteShip2.setPosition(spriteShip2.getPosition().x + (ship2Speed * dt.asSeconds()), spriteShip2.getPosition().y);

				// Has the ship reached the right hand edge of the screen?
				if (spriteShip2.getPosition().x > 1920)
				{
					// Set it up ready to be a whole new ship next frame
					ship2Active = false;
				}
			}

			// ship 3
			if (!ship3Active)
			{

				// How fast is the ship
				srand((int)time(0) * 30);
				ship3Speed = (rand() % 200);

				// How high is the ship
				srand((int)time(0) * 30);
				float height = (rand() % 450) - 150;
				spriteShip3.setPosition(-200, height);
				ship3Active = true;

				// Generate random scale factor between minScale and maxScale
				ship3Scale = minScale + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxScale - minScale)));

				// Update ship's scale
				spriteShip3.setScale(ship1Scale, ship1Scale);
			}
			else
			{

				spriteShip3.setPosition(spriteShip3.getPosition().x + (ship3Speed * dt.asSeconds()), spriteShip3.getPosition().y);

				// Has the ship reached the right hand edge of the screen?
				if (spriteShip3.getPosition().x > 1920)
				{
					// Set it up ready to be a whole new ship next frame
					ship3Active = false;
				}
			}

			// Update the score text
			std::stringstream ss;
			ss << "Score: " << score;
			scoreText.setString(ss.str());

			// Update the branch sprites
			for (int i = 0; i < NUM_BRANCHES; i++)
			{
				float height = i * 150;
				
				if (branchPositions[i] == side::LEFT)
				{
					// Move the sprite to the left side
					branches[i].setPosition(600, height);
					// Flip the sprite around the other way
					branches[i].setRotation(180);
				}
				else if (branchPositions[i] == side::RIGHT)
				{
					// Move the sprite to the right side
					branches[i].setPosition(1330, height);
					// Flip the sprite rotation to normal
					branches[i].setRotation(0);
				}
				else
				{
					// Hide the branch
					branches[i].setPosition(3000, height);
				}
			}

		}// End if(!pause)

		/*
		****************************************
		Draw the scene
		****************************************
		*/

		// Clear everything from the last frame
		window.clear();

		// Draw our game scene here
		window.draw(spriteBackground);

		// Draw the ships
		window.draw(spriteShip1);
		window.draw(spriteShip2);
		window.draw(spriteShip3);

		// Draw the branches
		for (int i = 0; i < NUM_BRANCHES; i++)
		{
			window.draw(branches[i]);
		}

		// Draw the tree
		window.draw(spriteTree);

		// Draw the insect
		window.draw(spriteBee);

		// Draw the score
		window.draw(scoreText);

		// Draw the timebar
		window.draw(timeBar);

		if (paused)
		{
			// Draw our message
			window.draw(messageText);
		}

		// Show everything we just drew
		window.display();
	}
	return 0;
}

// Function definition
void updateBranches(int seed)
{
	// Move all the branches down one place
	for (int j = NUM_BRANCHES - 1; j > 0; j--)
	{
		branchPositions[j] = branchPositions[j - 1];
	}

	// Spawn a new branch at position 0
	// LEFT, RIGHT, or NONE
	srand((int)time(0) + seed);
	int r = (rand() % 5);

	switch (r)
	{
		case 0:
			branchPositions[0] = side::LEFT;
				break;

		case 1:
			branchPositions[0] = side::RIGHT;

		default:
			branchPositions[0] = side::NONE;
			break;
	}
}