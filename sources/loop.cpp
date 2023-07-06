#include "emergence.hpp"

int loop(sf::RenderWindow &window, json file)
{
	// Initialize the physics clock
	sf::Clock clock;
	float last_time = 0;
	float current_time = clock.getElapsedTime().asSeconds();

	// Initialize the GUI parameters
	sf::Clock gui_clock;
	ImGui::SetNextWindowSize(ImVec2(300, 300));

	// Initialize the simulation parameters
	std::vector<particle_type *> types;
	std::vector<std::vector<float>> interactions;
	std::vector<std::vector<Particle *>> particles;

	init_simulation(file, types, interactions, particles);

	while (window.isOpen())
	{
		// Compute the physics delta_t
		last_time = current_time;
		current_time = clock.getElapsedTime().asSeconds();
		if (my_settings.get_pause() == false)
			my_settings.set_delta_t(current_time - last_time);
		else
			my_settings.set_delta_t(0.f);

		// Handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) // I have to check explicity for the type of event AND the key that was pressed because imGui generates escape key press events on its own...
				window.close();
		}

		ImGui::SFML::Update(window, gui_clock.restart());
		gui(types, interactions, particles, window);

		// Update physics parameters that may have changed
		update_simulation(types, interactions, particles);

		// Main clear+draw+display loop
		window.clear();

		// Update the particles
		compute_particles(particles, interactions);
		update_particles(particles);
		draw_particles(window, particles);

		ImGui::SFML::Render(window);

		window.display();
	}

	// Free memory
	for (auto &particles_type : particles)
		for (auto &particle : particles_type)
			delete particle;
	for (auto &type : types)
		delete type;

	ImGui::SFML::Shutdown();

	return EXIT_SUCCESS;
}
