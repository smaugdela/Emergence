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
	void save_to_json(std::string filename, std::vector<particle_type *> &types, std::vector<std::vector<float>> &interactions);
	void load_from_json(json json_settings);

	// Getters
	float get_width() const;
	float get_height() const;
	float get_depth() const;
	std::string get_title() const;
	unsigned int get_antialiasing_level() const;
	float get_particle_size() const;
	unsigned int get_particle_number() const;
	float get_force_factor() const;
	unsigned int get_fps_limit() const;
	float get_friction_coefficient() const;
	float get_delta_t() const;
	float get_boundary_limit() const;
	float get_max_range() const;
	bool get_3d() const;
	float get_temperature() const;

	// Setters
	void set_width(float width);
	void set_height(float height);
	void set_depth(float depth);
	void set_title(std::string title);
	void set_antialiasing_level(unsigned int antialiasing_level);
	void set_particle_size(float particle_size);
	void set_particle_number(unsigned int particle_number);
	void set_force_factor(float force_factor);
	void set_fps_limit(unsigned int framerate_limit);
	void set_friction_coefficient(float friction_coefficient);
	void set_delta_t(float delta_t);
	void set_boundary_limit(float boundary_limit);
	void set_max_range(float max_range);
	void set_3d(bool _3d);
	void set_temperature(float temperature);

private:
	void init_simulation(std::vector<particle_type> &types, std::vector<std::vector<float>> &interactions, std::vector<Particle *> &particles);

	// Window settings
	float width;
	float height;
	float depth;

	std::string title;
	unsigned int fps_limit;

	unsigned int antialiasing_level; // x4 is pretty enough.

	// Simulation settings
	float particle_size;
	unsigned int particle_number;
	float force_factor;
	float friction_coefficient;
	float temperature;
	float delta_t;		  // This is the time between two physical frames.
	float boundary_limit; // This is the ratio of the distance between two particles over maximum range at which they repell
	float max_range;	  // This is the maximum range at which two particles interact
	bool _3d;
};

std::ostream &operator<<(std::ostream &o, Settings const &i);

#endif /* ******************************************************** SETTINGS_H */
