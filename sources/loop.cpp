#include "emergence.hpp"

int loop(sf::RenderWindow &window)
{

	particle_type type = {0, sf::Color::Red, {{0, 1}}};
	std::vector<Particle> particles;
	for (int i = 0; i < PARTICLE_NUMBER; i++)
	{
		particles.push_back(Particle(type));
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
				window.close();
		}

		window.clear();

		for (std::vector<Particle>::iterator it = particles.begin(); it != particles.end(); ++it)
		{
			it->draw(window);
		}

		window.display();
	}

	return EXIT_SUCCESS;
}
