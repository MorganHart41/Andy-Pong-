// This code expands on the tutorial code provided at:
// http://www.sfml-dev.org/tutorials/2.3/start-vc.php

#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Mad Pong Skills");
	sf::CircleShape shape(100.f);
	sf::CircleShape shape2(12);
	shape.setFillColor(sf::Color::Green);
	shape2.setFillColor(sf::Color::Magenta);

	//First Paddle
	sf::RectangleShape paddle(sf::Vector2f(10, 40));
	paddle.setFillColor(sf::Color::Cyan);
	//Second Paddle
	sf::RectangleShape paddle1(sf::Vector2f(10, 40));
	paddle1.setFillColor(sf::Color::Red);

	int i = 0;
	while (window.isOpen())
	{
		sf::Event event;
		sf::Event event1;

		//window.draw(s);
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				// move the paddle up and down depending on
				// which key is pressed
				if (event.key.code == sf::Keyboard::W) // move up
				{
					paddle.setPosition(4, 4 + (--i));
				}
				if (event.key.code == sf::Keyboard::S) // move down
				{
					paddle.setPosition(4, 4 + (++i));
				}
				if (event1.key.code == sf::Keyboard::P) // move up
				{
					paddle.setPosition(400, 4 + (--i));
				}
				if (event1.key.code == sf::Keyboard::L) // move down
				{
					paddle.setPosition(400, 4 + (++i));
				}
			}
		}

		window.clear();

		/*if (i > 200)
		{
		i = 0;
		}
		i += 2;
		shape2.setPosition(4 + i, 200);
		window.draw(shape2);*/
		window.draw(paddle); // draw the paddle in the new position
		window.draw(paddle1);
		window.display();


	}

	return 0;
}