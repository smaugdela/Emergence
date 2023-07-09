#include "emergence.hpp"

void init_simulation(json file, std::vector<particle_type *> &types, std::vector<std::vector<float>> &interactions, std::vector<std::vector<Particle *>> &particles)
{
	// Read the settings file to initialize the types vector
	if (file.contains("types"))
	{
		size_t id = 0;
		for (auto &type : file["types"])
		{
			particle_type *new_type = new particle_type();
			new_type->id = id;
			new_type->color = sf::Color(type["color"][0], type["color"][1], type["color"][2]);
			new_type->amount = type["amount"];
			types.push_back(new_type);
			++id;
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
		for (size_t i = 0; i < types.size(); ++i)
		{
			std::vector<float> interaction;
			for (size_t j = 0; j < types.size(); ++j)
			{
				interaction.push_back(new_interactions[i * types.size() + j]);
			}
			interactions.push_back(interaction);
		}
	}

	if (types.size() == 0)
	{
		particle_type *type = new particle_type();
		type->id = 0;
		type->color = sf::Color::Blue;
		type->amount = my_settings.get_particle_number();
		types.push_back(type);

		std::vector<float> interaction;
		interaction.push_back(1.0f);
		interactions.push_back(interaction);
	}

	// Initialize particles vector from types vector

	for (size_t id = 0; id < types.size(); id++)
	{
		std::vector<Particle *> type_particles;
		for (size_t i = 0; i < types[id]->amount; i++)
		{
			type_particles.push_back(new Particle(types[id]));
		}
		particles.push_back(type_particles);
	}
}

// Change the simulation parameters that may have changed
void update_simulation(std::vector<particle_type *> &types, std::vector<std::vector<float>> &interactions, std::vector<std::vector<Particle *>> &particles)
{
	(void)interactions;
	// Update particles amounts
	for (size_t i = 0; i < particles.size(); i++)
	{
		if (particles[i].size() > types[i]->amount)
		{
			// Delete the particles
			for (size_t j = 0; j < particles[i].size() - types[i]->amount; j++)
			{
				delete particles[i][j];
			}
			particles[i].erase(particles[i].begin(), particles[i].begin() + particles[i].size() - types[i]->amount);
		}
		else if (particles[i].size() < types[i]->amount)
		{
			// Add the particles
			for (size_t j = 0; j < types[i]->amount - particles[i].size(); j++)
			{
				particles[i].push_back(new Particle(types[i]));
			}
		}
	}
}

// Compute the next state of the particle, but does not update it in order to let the other particles update at the same state
void compute_particles(std::vector<std::vector<Particle *>> &particles, std::vector<std::vector<float>> &interactions)
{
	// Compute the particles
	for (auto &type_particles : particles)
	{
		for (auto &particle : type_particles)
		{
			// Compute the acceleration
			particle->compute(particles, interactions);
		}
	}
}

// Update the particles with the new state computed in compute_particles
void update_particles(std::vector<std::vector<Particle *>> &particles)
{
	// Update the particles
	for (auto &type_particles : particles)
	{
		for (auto &particle : type_particles)
		{
			// Compute the acceleration
			particle->update();
		}
	}
}

void draw_particles(sf::RenderWindow &window, std::vector<std::vector<Particle *>> &particles)
{
	// Draw the particles
	for (auto &type_particles : particles)
	{
		for (auto &particle : type_particles)
		{
			// Compute the acceleration
			particle->draw(window);
		}
	}
}
