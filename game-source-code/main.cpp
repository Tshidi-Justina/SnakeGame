/** \file main.cpp
		\brief Contains the main function

		NB:to document global objects (functions, typedefs, enum, macros, etc), you must document the file in which they are defined. That is,
		you must provide this file comment block.
 */

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "pong-paddle.h"

// Define some global constants						
const int gameWidth = 800; 						// The width of the game screen
const int gameHeight = 600;						// The height of the game screen
const sf::Vector2f paddleSize{20, 20};			// The dimensions of the paddle's rectangle

/** \fn int main()
 *  \brief This function contains the majority of the code for the game
 *
 *  \return The application exit code: 0 for successful completion; a negative number to indicate an error
 *
 */

int main()
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	// Create the window of the application
	sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight, 32), "SFML SNAKE", sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true);

	auto leftPaddle = makeLeftPaddle();

	// Load the text font
	sf::Font font;
	if (!font.loadFromFile("resources/sansation.ttf"))
		return EXIT_FAILURE;

	// Initialize the pause message
	sf::Text pauseMessage;
	pauseMessage.setFont(font);
	pauseMessage.setCharacterSize(40);
	pauseMessage.setPosition(170.f, 150.f);
	pauseMessage.setFillColor(sf::Color::White);
	pauseMessage.setString("Welcome to SFML PONG!\nPress space to start the game");

	// Define the paddles properties
	const float paddleSpeed = 400.f;

	sf::Clock clock;
	bool isPlaying = false;
	while (window.isOpen())
	{
		// Handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Window closed or escape key pressed: exit
			if ((event.type == sf::Event::Closed) ||
					((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
			{
				window.close();
				break;
			}

			// Space key pressed: play
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
			{
				if (!isPlaying)
				{
					// (re)start the game
					isPlaying = true;
					clock.restart();

					// Reset the position of the paddles and ball
					leftPaddle.setPosition(10 + leftPaddleSize.x / 2, gameHeight / 2);

				}
			}
		}

		if (isPlaying)
		{
			float deltaTime = clock.restart().asSeconds();

			// Move the player's paddle
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (leftPaddle.getPosition().y - leftPaddleSize.y / 2 > 5.f))
			{
				leftPaddle.move(0.f, -paddleSpeed * deltaTime);
			}
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
					(leftPaddle.getPosition().y + leftPaddleSize.y / 2 < gameHeight - 5.f))
			{
				leftPaddle.move(0.f, paddleSpeed * deltaTime);
			}

		}

		// Clear the window
		window.clear(sf::Color(50, 200, 50));

		if (isPlaying)
		{
			// Draw the paddles and the ball
			window.draw(leftPaddle);
		}
		else
		{
			// Draw the pause message
			window.draw(pauseMessage);
		}

		// Display things on screen
		window.display();
	}

	return EXIT_SUCCESS;
}