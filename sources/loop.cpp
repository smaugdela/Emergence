#include "emergence.hpp"

int loop(sf::RenderWindow &window)
{
	sf::Clock clock;
	float last_time = 0;
	float current_time;

	// Compute mean fps
	size_t iteration = 0;
	size_t fps_sum = 0;
	size_t fps = 0;
	// std::string str_fps;

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
		if (iteration == 0)
			fps = 0;
		else
			fps = 1.f / (current_time - last_time);
		// str_fps = std::to_string(fps);
		last_time = current_time;
		fps_sum += fps;
		iteration++;
		// fps_counter(window, str_fps);

		// Limit the framerate
		while (my_settings.get_fps_limit() > 0 && (clock.getElapsedTime().asSeconds() - current_time) < 1.f / my_settings.get_fps_limit())
			;

		window.display();
	}

	// Compute mean fps
	std::cout << "Mean FPS: " << fps_sum / iteration << std::endl;

	return EXIT_SUCCESS;
}
