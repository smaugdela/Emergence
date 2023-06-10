#include "emergence.hpp"

int loop(sf::RenderWindow &window)
{
	particle_type type;
	type.id = 0;
	type.color = sf::Color::Red;

	// Initialize a vector of interactions
	std::vector<std::vector<int>> interactions;
	std::vector<int> interaction = {0, 1};
	interactions.push_back(interaction);

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
			it->update();
			it->draw(window);
		}

		window.display();
	}

	return EXIT_SUCCESS;
}
