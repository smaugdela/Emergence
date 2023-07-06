#include "emergence.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Settings::Settings()
{
	// Initialise using macros.
	unsigned int antialiasing_level, particle_number;
	std::string title;
	float width, height, depth, temperature, particle_size, force_factor, friction_coefficient, delta_t, boundary_limit, max_range;
	bool _3d, doppler_effect, pause, energy_conservation;

	width = WIDTH;
	this->set_width(width);

	height = HEIGHT;
	this->set_height(height);

	depth = DEPTH;
	this->set_depth(depth);

	title = TITLE;
	this->set_title(title);

	antialiasing_level = ANTIALIASING_LEVEL;
	this->set_antialiasing_level(antialiasing_level);

	particle_size = PARTICLE_RADIUS;
	this->set_particle_size(particle_size);

	particle_number = PARTICLE_NUMBER;
	this->set_particle_number(particle_number);

	force_factor = FORCE_FACTOR;
	this->set_force_factor(force_factor);

	fps_limit = FPS_LIMIT;
	this->set_fps_limit(fps_limit);

	friction_coefficient = FRICTION_COEFFICIENT;
	this->set_friction_coefficient(friction_coefficient);

	delta_t = DELTA_T;
	this->set_delta_t(delta_t);

	boundary_limit = BOUNDARY_LIMIT;
	this->set_boundary_limit(boundary_limit);

	max_range = MAX_RANGE;
	this->set_max_range(max_range);

	_3d = _3D;
	this->set_3d(_3d);

	temperature = TEMPERATURE;
	this->set_temperature(temperature);

	doppler_effect = DOPPLER_EFFECT;
	this->set_doppler_effect(doppler_effect);

	energy_conservation = ENERGY_CONSERVATION;
	this->set_energy_conservation(energy_conservation);

	pause = PAUSE;
	this->set_pause(pause);
}

Settings::Settings(const Settings &src)
{
	*this = src;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Settings::~Settings()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Settings &Settings::operator=(Settings const &rhs)
{
	if (this != &rhs)
	{
		this->width = rhs.width;
		this->height = rhs.height;
		this->depth = rhs.depth;
		this->title = rhs.title;
		this->antialiasing_level = rhs.antialiasing_level;
		this->particle_size = rhs.particle_size;
		this->particle_number = rhs.particle_number;
		this->force_factor = rhs.force_factor;
		this->fps_limit = rhs.fps_limit;
		this->friction_coefficient = rhs.friction_coefficient;
		this->delta_t = rhs.delta_t;
		this->boundary_limit = rhs.boundary_limit;
		this->max_range = rhs.max_range;
		this->_3d = rhs._3d;
		this->temperature = rhs.temperature;
		this->doppler_effect = rhs.doppler_effect;
		this->energy_conservation = rhs.energy_conservation;
		this->pause = rhs.pause;
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, Settings const &i)
{
	o << "Width: " << i.get_width() << std::endl;
	o << "Height: " << i.get_height() << std::endl;
	o << "Depth: " << i.get_depth() << std::endl;
	o << "Title: " << i.get_title() << std::endl;
	o << "Antialiasing level: " << i.get_antialiasing_level() << std::endl;
	o << "Particle size: " << i.get_particle_size() << std::endl;
	o << "Particle number: " << i.get_particle_number() << std::endl;
	o << "Max acceleration: " << i.get_force_factor() << std::endl;
	o << "fps_limit: " << i.get_fps_limit() << std::endl;
	o << "Friction: " << i.get_friction_coefficient() << std::endl;
	o << "Delta t: " << i.get_delta_t() << std::endl;
	o << "Boundary limit: " << i.get_boundary_limit() << std::endl;
	o << "Max range: " << i.get_max_range() << std::endl;
	o << "3D: " << i.get_3d() << std::endl;
	o << "Temperature: " << i.get_temperature() << std::endl;
	o << "Doppler effect: " << i.get_doppler_effect() << std::endl;
	o << "Energy conservation: " << i.get_energy_conservation() << std::endl;
	o << "Pause: " << i.get_pause() << std::endl;
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void Settings::save_to_json(std::string filename, std::vector<particle_type *> &types, std::vector<std::vector<float>> &interactions)
{
	// Save the settings to a json file
	std::ofstream file(filename);
	json json_settings;

	json_settings["title"] = this->get_title();
	json_settings["antialiasing_level"] = this->get_antialiasing_level();
	json_settings["particle_size"] = this->get_particle_size();
	json_settings["force_factor"] = this->get_force_factor();
	json_settings["friction_coefficient"] = this->get_friction_coefficient();
	json_settings["boundary_limit"] = this->get_boundary_limit();
	json_settings["max_range"] = std::sqrt(this->get_max_range());
	json_settings["3D"] = this->get_3d();
	json_settings["temperature"] = this->get_temperature();
	json_settings["doppler_effect"] = this->get_doppler_effect();
	json_settings["energy_conservation"] = this->get_energy_conservation();
	json_settings["pause"] = this->get_pause();

	json_settings["types"] = json::array();
	for (auto &type : types)
	{
		json json_type;
		json_type["id"] = type->id;

		json json_color;
		json_color[0] = type->color.r;
		json_color[1] = type->color.g;
		json_color[2] = type->color.b;
		json_type["color"] = json_color;

		json_type["amount"] = type->amount;

		json_settings["types"].push_back(json_type);
	}

	json_settings["interactions"] = json::array();
	for (auto &interaction : interactions)
	{
		for (auto &value : interaction)
			json_settings["interactions"].push_back(value);
	}

	file << json_settings;
	file.close();
}

void Settings::load_from_json(json json_settings)
{
	// Load the settings from the json file
	if (json_settings.contains("width"))
		this->set_width(json_settings["width"]);

	if (json_settings.contains("height"))
		this->set_height(json_settings["height"]);

	if (json_settings.contains("depth"))
		this->set_depth(json_settings["depth"]);

	if (json_settings.contains("title"))
		this->set_title(json_settings["title"]);

	if (json_settings.contains("antialiasing_level"))
		this->set_antialiasing_level(json_settings["antialiasing_level"]);

	if (json_settings.contains("particle_size"))
		this->set_particle_size(json_settings["particle_size"]);

	if (json_settings.contains("particle_number"))
		this->set_particle_number(json_settings["particle_number"]);

	if (json_settings.contains("force_factor"))
		this->set_force_factor(json_settings["force_factor"]);

	if (json_settings.contains("fps_limit"))
		this->set_fps_limit(json_settings["fps_limit"]);

	if (json_settings.contains("friction_coefficient"))
		this->set_friction_coefficient(json_settings["friction_coefficient"]);

	if (json_settings.contains("delta_t"))
		this->set_delta_t(json_settings["delta_t"]);

	if (json_settings.contains("boundary_limit"))
		this->set_boundary_limit(json_settings["boundary_limit"]);

	if (json_settings.contains("max_range"))
		this->set_max_range(json_settings["max_range"]);

	if (json_settings.contains("3D"))
		this->set_3d(json_settings["3D"]);

	if (json_settings.contains("temperature"))
		this->set_temperature(json_settings["temperature"]);

	if (json_settings.contains("doppler_effect"))
		this->set_doppler_effect(json_settings["doppler_effect"]);

	if (json_settings.contains("energy_conservation"))
		this->set_energy_conservation(json_settings["energy_conservation"]);

	if (json_settings.contains("pause"))
		this->set_pause(json_settings["pause"]);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

// Setters
void Settings::set_width(float width)
{
	if (width < 100.f)
	{
		width = 100.f;
		std::cerr << "Width is too small, it has been set to 100." << std::endl;
	}
	else if (width > 4000.f)
	{
		width = 4000.f;
		std::cerr << "Width is too big, it has been set to 4000." << std::endl;
	}
	this->width = width;
}

void Settings::set_height(float height)
{
	if (height < 100.f)
	{
		height = 100.f;
		std::cerr << "Height is too small, it has been set to 100." << std::endl;
	}
	else if (height > 4000.f)
	{
		height = 4000.f;
		std::cerr << "Height is too big, it has been set to 4000." << std::endl;
	}
	this->height = height;
}

void Settings::set_depth(float depth)
{
	if (depth < 100.f)
	{
		depth = 100.f;
		std::cerr << "Depth is too small, it has been set to 100." << std::endl;
	}
	else if (depth > 4000.f)
	{
		depth = 4000.f;
		std::cerr << "Depth is too big, it has been set to 4000." << std::endl;
	}
	this->depth = depth;
}

void Settings::set_title(std::string title)
{
	this->title = title;
}

void Settings::set_antialiasing_level(unsigned int antialiasing_level)
{
	if (antialiasing_level < 1)
	{
		antialiasing_level = 0;
		std::cerr << "Antialiasing level is too small, it has been set to 1." << std::endl;
	}
	else if (antialiasing_level > 16)
	{
		antialiasing_level = 16;
		std::cerr << "Antialiasing level is too big, it has been set to 16." << std::endl;
	}
	this->antialiasing_level = antialiasing_level;
}

void Settings::set_particle_size(float particle_size)
{
	if (particle_size < 1.0f)
	{
		particle_size = 1.0f;
		std::cerr << "Particle size is too small, it has been set to 1." << std::endl;
	}
	else if (particle_size > 10.0f)
	{
		particle_size = 10.0f;
		std::cerr << "Particle size is too big, it has been set to 10." << std::endl;
	}
	this->particle_size = particle_size;
}

void Settings::set_particle_number(unsigned int particle_number)
{
	if (particle_number < 1)
	{
		particle_number = 1;
		std::cerr << "Particle number is too small, it has been set to 1." << std::endl;
	}
	else if (particle_number > 1000000)
	{
		particle_number = 1000000;
		std::cerr << "Particle number is too big, it has been set to 1000000." << std::endl;
	}
	this->particle_number = particle_number;
}

void Settings::set_force_factor(float force_factor)
{
	if (force_factor < 1.0f)
	{
		force_factor = 1.0f;
		std::cerr << "Force factor is too small, it has been set to 1." << std::endl;
	}
	else if (force_factor > width * 10.f)
	{
		force_factor = width * 10.f;
		std::cerr << "Force factor is too big, it has been set to width * 10: " << this->width * 10.f << std::endl;
	}
	this->force_factor = force_factor;
}

void Settings::set_fps_limit(unsigned int fps_limit)
{

	if (fps_limit > 1000)
	{
		fps_limit = 1000;
		std::cerr << "FPS limit is too big, it has been set to 1000." << std::endl;
	}
	this->fps_limit = fps_limit;
}

void Settings::set_friction_coefficient(float friction_coefficient)
{
	if (friction_coefficient < 0.f)
	{
		friction_coefficient = 0;
		std::cerr << "Friction coefficient cannot be negative (maybe later, that could be fun)." << std::endl;
	}
	else if (friction_coefficient > 1.f)
	{
		friction_coefficient = 1.f;
		std::cerr << "Friction coefficient is too big, it has been set to 100%." << std::endl;
	}
	this->friction_coefficient = friction_coefficient;
}

void Settings::set_delta_t(float delta_time)
{
	if (delta_time < 0.0f)
	{
		delta_time = 0.0f;
		std::cerr << "Delta time cannot be negative." << std::endl;
	}
	else if (delta_time > 1.0f)
	{
		delta_time = 1.0f;
		std::cerr << "Delta time is too big, it has been set to 1.0." << std::endl;
	}
	this->delta_t = delta_time;
}

void Settings::set_boundary_limit(float boundary_limit)
{
	if (boundary_limit < 0.f)
	{
		boundary_limit = 0.f;
		std::cerr << "Boundary limit cannot be negative." << std::endl;
	}
	else if (boundary_limit > 1.f)
	{
		boundary_limit = 1.f;
		std::cerr << "Boundary limit is too big, it has been set to 100%." << std::endl;
	}
	this->boundary_limit = boundary_limit;
}

void Settings::set_max_range(float max_range)
{
	if (max_range < 0.f)
	{
		max_range = 0.f;
		std::cerr << "Max range cannot be negative." << std::endl;
	}
	this->max_range = std::pow(max_range, 2); // Setting the max range to the square of the value to avoid sqrt() in the distance calculation
}

void Settings::set_3d(bool is_3d)
{
	this->_3d = is_3d;
}

void Settings::set_temperature(float temperature)
{
	if (temperature < 0.f)
	{
		temperature = 0.f;
		std::cerr << "Temperature cannot be negative." << std::endl;
	}
	else if (temperature > 1.f)
	{
		temperature = 1.f;
		std::cerr << "Temperature is too big, it has been set to 1." << std::endl;
	}
	this->temperature = temperature;
}

void Settings::set_doppler_effect(bool doppler_effect)
{
	this->doppler_effect = doppler_effect;
}

void Settings::set_energy_conservation(bool energy_conservation)
{
	this->energy_conservation = energy_conservation;
}

void Settings::set_pause(bool pause)
{
	this->pause = pause;
}

// Getters
float Settings::get_width() const
{
	return this->width;
}

float Settings::get_height() const
{
	return this->height;
}

float Settings::get_depth() const
{
	return this->depth;
}

std::string Settings::get_title() const
{
	return this->title;
}

unsigned int Settings::get_antialiasing_level() const
{
	return this->antialiasing_level;
}

float Settings::get_particle_size() const
{
	return this->particle_size;
}

unsigned int Settings::get_particle_number() const
{
	return this->particle_number;
}

float Settings::get_force_factor() const
{
	return this->force_factor;
}

unsigned int Settings::get_fps_limit() const
{
	return this->fps_limit;
}

float Settings::get_friction_coefficient() const
{
	return this->friction_coefficient;
}

float Settings::get_delta_t() const
{
	return this->delta_t;
}

float Settings::get_boundary_limit() const
{
	return this->boundary_limit;
}

float Settings::get_max_range() const
{
	return this->max_range;
}

bool Settings::get_3d() const
{
	return this->_3d;
}

float Settings::get_temperature() const
{
	return this->temperature;
}

bool Settings::get_doppler_effect() const
{
	return this->doppler_effect;
}

bool Settings::get_energy_conservation() const
{
	return this->energy_conservation;
}

bool Settings::get_pause() const
{
	return this->pause;
}

/* ************************************************************************** */
