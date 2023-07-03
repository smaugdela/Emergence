#include "emergence.hpp"

static void init_simulation(std::vector<particle_type> &types, std::vector<std::vector<float>> &interactions, std::vector<Particle *> &particles)
{
	// Initialize the types vector
	// Hardcoded for the moment
	particle_type type;
	type.id = 0;
	type.color = sf::Color::Blue;
	type.amount = my_settings.get_particle_number();
	types.push_back(type);

	// type.id = 1;
	// type.color = sf::Color::Green;
	// type.amount = this->get_particle_number() / 3;
	// types.push_back(type);

	// type.id = 2;
	// type.color = sf::Color::Red;
	// type.amount = this->get_particle_number() / 3;
	// types.push_back(type);

	// Initialize the interactions vector
	// Hardcoded for the moment
	// Matrix looking like this:
	// 0 0.5 1
	// 0.5 0 1
	// 1 1 0
	std::vector<float> interaction;
	interaction.push_back(0.2f);
	// interaction.push_back(0.5f);
	// interaction.push_back(1.0f);
	interactions.push_back(interaction);
	// interaction.clear();
	// interaction.push_back(0.5f);
	// interaction.push_back(0.0f);
	// interaction.push_back(1.0f);
	// interactions.push_back(interaction);
	// interaction.clear();
	// interaction.push_back(1.0f);
	// interaction.push_back(1.0f);
	// interaction.push_back(0.0f);
	// interactions.push_back(interaction);

	// Initialize the particles vector
	size_t id = 0;
	for (size_t i = 0; i < types.size(); i++)
	{
		for (size_t j = 0; j < types[i].amount; j++)
		{
			particles.push_back(new Particle(types[i], id));
			++id;
		}
	}
}

static void compute_particles(std::vector<Particle *> &particles, std::vector<std::vector<float>> &interactions)
{
	// Update the particles
	for (size_t i = 0; i < particles.size(); i++)
	{
		// Update the acceleration
		particles[i]->compute(particles, interactions);
	}
}

static void update_particles(std::vector<Particle *> &particles)
{
	// Update the particles
	for (size_t i = 0; i < particles.size(); i++)
	{
		// Update the acceleration
		particles[i]->update();
	}
}

static void draw_particles(sf::RenderWindow &window, std::vector<Particle *> &particles)
{
	// Draw the particles
	for (size_t i = 0; i < particles.size(); i++)
	{
		particles[i]->draw(window);
	}
}

int loop(sf::RenderWindow &window)
{
	sf::Clock clock;
	float last_time = 0;
	float current_time = clock.getElapsedTime().asSeconds();

	std::vector<particle_type> types;
	std::vector<std::vector<float>> interactions;
	std::vector<Particle *> particles;

	init_simulation(types, interactions, particles);

	// Compute mean fps
	size_t iteration = 0;
	float delta_t_sum = 0;
	// size_t fps = 0;
	// std::string str_fps;

	while (window.isOpen())
	{
		last_time = current_time;
		current_time = clock.getElapsedTime().asSeconds();
		my_settings.set_delta_t(current_time - last_time);

		++iteration;
		delta_t_sum += my_settings.get_delta_t();

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
		compute_particles(particles, interactions);
		update_particles(particles);
		draw_particles(window, particles);

		// Limit the framerate
		// while (my_settings.get_fps_limit() > 0 && (clock.getElapsedTime().asSeconds() - current_time) < 1.f / my_settings.get_fps_limit())
		// 	;

		window.display();
	}

	// Free memory
	for (size_t i = 0; i < particles.size(); i++)
	{
		delete particles[i];
	}

	// Print mean fps
	std::cout << "Mean fps: " << 1.0f / (delta_t_sum / float(iteration)) << std::endl;

	return EXIT_SUCCESS;
}
