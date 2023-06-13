#include "emergence.hpp"

int loop(sf::RenderWindow &window)
{
	sf::Clock clock;
	float last_time = 0;
	float current_time;

	while (window.isOpen())
	{

		current_time = clock.getElapsedTime().asSeconds();

		// Handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
				window.close();
		}

		// Main clear+draw+display loop
		window.clear();

		// Update the particles
		my_settings.compute_particles();
		my_settings.update_particles();
		my_settings.draw_particles(window);

		// Display the FPS
		std::string fps = std::to_string(1.f / (current_time - last_time));
		last_time = current_time;
		fps_counter(window, fps);

		// Limit the framerate
		// while (my_settings.get_fps_limit() && (clock.getElapsedTime().asSeconds() - current_time) < 1.f / 60.f)
		// 	;

		window.display();
	}

	return EXIT_SUCCESS;
}
