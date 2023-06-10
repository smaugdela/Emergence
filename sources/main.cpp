#include "emergence.hpp"

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), TITLE, sf::Style::Default, settings);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
				window.close();
		}

		window.clear();

		// Draw 3 circles
		sf::CircleShape circle1(100.f);
		circle1.setFillColor(sf::Color::Red);
		circle1.setPosition(100.f, 100.f);
		window.draw(circle1);

		sf::CircleShape circle2(100.f);
		circle2.setFillColor(sf::Color::Green);
		circle2.setPosition(300.f, 100.f);
		window.draw(circle2);

		sf::CircleShape circle3(100.f);
		circle3.setFillColor(sf::Color::Blue);
		circle3.setPosition(500.f, 100.f);
		window.draw(circle3);

		window.display();
	}

	return EXIT_SUCCESS;
}
