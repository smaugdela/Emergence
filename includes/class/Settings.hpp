#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <iostream>
#include <string>
#include <vector>
#include "Particle.hpp"

class Settings
{

public:
	// Constructors
	Settings();
	Settings(Settings const &src);

	// Destructor
	~Settings();

	// Overload
	Settings &operator=(Settings const &rhs);

	// Methods
	// void add_type(particle_type type);
	void compute_particles(void);
	void update_particles(void);
	void draw_particles(sf::RenderWindow &window) const;

	// Getters
	unsigned int get_width() const;
	unsigned int get_height() const;
	std::string get_title() const;
	unsigned int get_antialiasing_level() const;
	float get_particle_size() const;
	unsigned int get_particle_number() const;
	unsigned int get_max_acceleration() const;
	unsigned int get_max_velocity() const;
	unsigned int get_grid_size() const;
	unsigned int get_fps_limit() const;
	std::vector<particle_type> get_types() const;
	std::vector<std::vector<float>> get_interactions() const;
	std::vector<Particle> get_particles() const;

	// Setters
	void set_width(unsigned int width);
	void set_height(unsigned int height);
	void set_title(std::string title);
	void set_antialiasing_level(unsigned int antialiasing_level);
	void set_particle_size(float particle_size);
	void set_particle_number(unsigned int particle_number);
	void set_max_acceleration(unsigned int max_acceleration);
	void set_max_velocity(unsigned int max_velocity);
	void set_grid_size(unsigned int grid_size);
	void set_fps_limit(unsigned int framerate_limit);

private:
	void init_simulation(std::vector<particle_type> &types, std::vector<std::vector<float>> &interactions, std::vector<Particle> &particles);

	// Window settings
	unsigned int width;
	unsigned int height;
	std::string title;
	unsigned int fps_limit;

	unsigned int antialiasing_level; // x4 is pretty enough.

	// Simulation settings
	float particle_size;
	unsigned int particle_number;
	unsigned int max_acceleration;
	unsigned int max_velocity;
	unsigned int grid_size; // This is the size of the subgrid used simulate particles.

	// Particles interactions
	std::vector<particle_type> types;
	std::vector<std::vector<float>> interactions;
	std::vector<Particle> particles;
};

std::ostream &operator<<(std::ostream &o, Settings const &i);

#endif /* ******************************************************** SETTINGS_H */
