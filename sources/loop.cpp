#include "emergence.hpp"

static void init_simulation(json file, std::vector<particle_type> &types, std::vector<std::vector<float>> &interactions, std::vector<Particle *> &particles)
{
	// Read the settings file to initialize the types vector
	if (file.contains("types"))
	{
		for (auto &type : file["types"])
		{
			particle_type new_type;
			new_type.id = type["id"];
			new_type.color = sf::Color(type["color"][0], type["color"][1], type["color"][2]);
			new_type.amount = type["amount"];
			types.push_back(new_type);
		}
	}

	// Read the settings file to initialize the interactions vector
	if (file.contains("interactions"))
	{
		std::vector<float> new_interactions = file["interactions"];
		if (new_interactions.size() != types.size() * types.size())
		{
			std::cerr << "Error: the number of interactions must be equal to the number of types" << std::endl;
			exit(EXIT_FAILURE);
		}
		for (size_t i = 0; i < types.size(); i++)
		{
			std::vector<float> interaction;
			for (size_t j = 0; j < types.size(); j++)
			{
				interaction.push_back(new_interactions[i * types.size() + j]);
			}
			interactions.push_back(interaction);
		}
	}

	if (types.size() == 0)
	{
		std::cout << "No file found, initializing with default values" << std::endl;
		particle_type type;
		type.id = 0;
		type.color = sf::Color::Blue;
		type.amount = my_settings.get_particle_number();
		types.push_back(type);

		std::vector<float> interaction;
		interaction.push_back(1.0f);
		interactions.push_back(interaction);
	}

	// Initialize particles vector from types vector
	size_t id = 0;
	for (auto &type : types)
	{
		for (size_t i = 0; i < type.amount; i++)
		{
			Particle *particle = new Particle(type, id);
			particles.push_back(particle);
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

int loop(sf::RenderWindow &window, json file)
{
	sf::Clock clock;
	float last_time = 0;
	float current_time = clock.getElapsedTime().asSeconds();

	std::vector<particle_type> types;
	std::vector<std::vector<float>> interactions;
	std::vector<Particle *> particles;

	init_simulation(file, types, interactions, particles);

	// Compute mean fps
	size_t iteration = 0;
	float delta_t_sum = 0;

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
