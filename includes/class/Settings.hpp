#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <iostream>
#include <string>
#include <vector>
#include "Particle.hpp"
#include "json.hpp"
using json = nlohmann::json;

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
	// void save_to_json(std::string filename);
	void load_from_json(json json_settings);

	// Getters
	unsigned int get_width() const;
	unsigned int get_height() const;
	std::string get_title() const;
	unsigned int get_antialiasing_level() const;
	float get_particle_size() const;
	unsigned int get_particle_number() const;
	float get_force_factor() const;
	float get_grid_size() const;
	unsigned int get_fps_limit() const;
	float get_friction_coefficient() const;
	float get_delta_t() const;
	float get_boundary_limit() const;
	float get_max_range() const;
	std::vector<particle_type> get_types() const;
	std::vector<std::vector<float>> get_interactions() const;
	std::vector<Particle *> get_particles() const;

	// Setters
	void set_width(unsigned int width);
	void set_height(unsigned int height);
	void set_title(std::string title);
	void set_antialiasing_level(unsigned int antialiasing_level);
	void set_particle_size(float particle_size);
	void set_particle_number(unsigned int particle_number);
	void set_force_factor(float force_factor);
	void set_grid_size(float grid_size);
	void set_fps_limit(unsigned int framerate_limit);
	void set_friction_coefficient(float friction_coefficient);
	void set_delta_t(float delta_t);
	void set_boundary_limit(float boundary_limit);
	void set_max_range(float max_range);

private:
	void init_simulation(std::vector<particle_type> &types, std::vector<std::vector<float>> &interactions, std::vector<Particle *> &particles);

	// Window settings
	unsigned int width;
	unsigned int height;
	std::string title;
	unsigned int fps_limit;

	unsigned int antialiasing_level; // x4 is pretty enough.

	// Simulation settings
	float particle_size;
	unsigned int particle_number;
	float force_factor;
	float grid_size; // This is the size of the subgrid used simulate particles.
	float friction_coefficient;
	float delta_t;		  // This is the time between two physical frames.
	float boundary_limit; // This is the ratio of the distance between two particles over maximum range at which they repell
	float max_range;	  // This is the maximum range at which two particles interact
};

std::ostream &operator<<(std::ostream &o, Settings const &i);

#endif /* ******************************************************** SETTINGS_H */
