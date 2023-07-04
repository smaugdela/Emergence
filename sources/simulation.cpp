#include "emergence.hpp"

void init_simulation(json file, std::vector<particle_type> &types, std::vector<std::vector<float>> &interactions, std::vector<Particle *> &particles)
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

// Compute the next state of the particle, but does not update it in order to let the other particles update at the same state
void compute_particles(std::vector<Particle *> &particles, std::vector<std::vector<float>> &interactions)
{
	// Update the particles
	for (size_t i = 0; i < particles.size(); i++)
	{
		// Update the acceleration
		particles[i]->compute(particles, interactions);
	}
}

// Update the particles with the new state computed in compute_particles
void update_particles(std::vector<Particle *> &particles)
{
	// Update the particles
	for (size_t i = 0; i < particles.size(); i++)
	{
		// Update the acceleration
		particles[i]->update();
	}
}

void draw_particles(sf::RenderWindow &window, std::vector<Particle *> &particles)
{
	// Draw the particles
	for (size_t i = 0; i < particles.size(); i++)
	{
		particles[i]->draw(window);
	}
}
