#include "emergence.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Settings::Settings()
{
	// Initialise using macros.
	unsigned int width, height, antialiasing_level, particle_number, max_acceleration, max_velocity, grid_size;
	std::string title;
	float particle_size;

	width = WIDTH;
	this->set_width(width);

	height = HEIGHT;
	this->set_height(height);

	title = TITLE;
	this->set_title(title);

	antialiasing_level = ANTIALIASING_LEVEL;
	this->set_antialiasing_level(antialiasing_level);

	particle_size = PARTICLE_SIZE;
	this->set_particle_size(particle_size);

	particle_number = PARTICLE_NUMBER;
	this->set_particle_number(particle_number);

	grid_size = GRID_SIZE;
	this->set_grid_size(grid_size);

	max_acceleration = MAX_ACCELERATION;
	this->set_max_acceleration(max_acceleration);

	max_velocity = MAX_VELOCITY;
	this->set_max_velocity(max_velocity);

	// Initialize the types, interactions and particles vectors
	init_simulation(this->types, this->interactions, this->particles);
}

void Settings::init_simulation(std::vector<particle_type> &types, std::vector<std::vector<float>> &interactions, std::vector<Particle> &particles)
{
	// Initialize the types vector
	// Hardcoded for the moment
	particle_type type;
	type.id = 0;
	type.color = sf::Color::Blue;
	type.amount = this->get_particle_number() / 3;
	types.push_back(type);

	type.id = 1;
	type.color = sf::Color::Green;
	type.amount = this->get_particle_number() / 3;
	types.push_back(type);

	type.id = 2;
	type.color = sf::Color::Red;
	type.amount = this->get_particle_number() / 3;
	types.push_back(type);

	// Initialize the interactions vector
	// Hardcoded for the moment
	// Matrix looking like this:
	// 0 0.5 1
	// 0.5 0 1
	// 1 1 0
	std::vector<float> interaction;
	interaction.push_back(0.0f);
	interaction.push_back(0.5f);
	interaction.push_back(1.0f);
	interactions.push_back(interaction);
	interaction.clear();
	interaction.push_back(0.5f);
	interaction.push_back(0.0f);
	interaction.push_back(1.0f);
	interactions.push_back(interaction);
	interaction.clear();
	interaction.push_back(1.0f);
	interaction.push_back(1.0f);
	interaction.push_back(0.0f);
	interactions.push_back(interaction);

	// Initialize the particles vector
	for (size_t i = 0; i < this->types.size(); i++)
	{
		for (size_t j = 0; j < this->types[i].amount; j++)
			particles.push_back(Particle(types[i]));
	}
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
		this->title = rhs.title;
		this->antialiasing_level = rhs.antialiasing_level;
		this->particle_size = rhs.particle_size;
		this->particle_number = rhs.particle_number;
		this->max_acceleration = rhs.max_acceleration;
		this->max_velocity = rhs.max_velocity;
		this->grid_size = rhs.grid_size;
		this->types = rhs.types;
		this->interactions = rhs.interactions;
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, Settings const &i)
{
	o << "Width: " << i.get_width() << std::endl;
	o << "Height: " << i.get_height() << std::endl;
	o << "Title: " << i.get_title() << std::endl;
	o << "Antialiasing level: " << i.get_antialiasing_level() << std::endl;
	o << "Particle size: " << i.get_particle_size() << std::endl;
	o << "Particle number: " << i.get_particle_number() << std::endl;
	o << "Max acceleration: " << i.get_max_acceleration() << std::endl;
	o << "Max velocity: " << i.get_max_velocity() << std::endl;
	o << "Grid size: " << i.get_grid_size() << std::endl;
	o << "Types: ";
	for (auto type : i.get_types())
		o << "id: " << type.id;
	o << std::endl;
	o << "Interactions: ";
	for (auto interaction : i.get_interactions())
	{
		for (auto type : interaction)
			o << type << " ";
		o << std::endl;
	}
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void Settings::update_particles()
{
	// Update the particles
	for (size_t i = 0; i < particles.size(); i++)
	{
		// Update the acceleration
		this->particles[i].update();
	}
}

void Settings::draw_particles(sf::RenderWindow &window) const
{
	// Draw the particles
	for (size_t i = 0; i < particles.size(); i++)
	{
		this->particles[i].draw(window);
	}
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

// Setters
void Settings::set_width(unsigned int width)
{
	if (width < 100)
	{
		width = 100;
		std::cerr << "Width is too small, it has been set to 100." << std::endl;
	}
	else if (width > 4000)
	{
		width = 4000;
		std::cerr << "Width is too big, it has been set to 4000." << std::endl;
	}
	this->width = width;
}

void Settings::set_height(unsigned int height)
{
	if (height < 100)
	{
		height = 100;
		std::cerr << "Height is too small, it has been set to 100." << std::endl;
	}
	else if (height > 4000)
	{
		height = 4000;
		std::cerr << "Height is too big, it has been set to 4000." << std::endl;
	}
	this->height = height;
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
	else if (particle_size > 50.0f)
	{
		particle_size = 50.0f;
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

void Settings::set_max_acceleration(unsigned int max_acceleration)
{
	if (max_acceleration < 1)
	{
		max_acceleration = 1;
		std::cerr << "Max acceleration is too small, it has been set to 1." << std::endl;
	}
	else if (max_acceleration > grid_size)
	{
		max_acceleration = grid_size;
		std::cerr << "Max acceleration is too big, it has been set to grid_size: " << this->grid_size << std::endl;
	}
	this->max_acceleration = max_acceleration;
}

void Settings::set_max_velocity(unsigned int max_velocity)
{
	if (max_velocity < 1)
	{
		max_velocity = 1;
		std::cerr << "Max velocity is too small, it has been set to 1." << std::endl;
	}
	else if (max_velocity > grid_size)
	{
		max_velocity = grid_size;
		std::cerr << "Max velocity is too big, it has been set to grid_size: " << this->grid_size << std::endl;
	}
	this->max_velocity = max_velocity;
}

void Settings::set_grid_size(unsigned int grid_size)
{
	if (grid_size < this->width || grid_size < this->height)
	{
		grid_size = std::max(this->width, this->height);
		std::cerr << "Grid size is too small, it has been set to " << grid_size << std::endl;
	}
	else if (grid_size > INT_MAX)
	{
		grid_size = INT_MAX;
		std::cerr << "Grid size is too big, it has been set to INT_MAX." << std::endl;
	}
	this->grid_size = grid_size;
}

// Getters
unsigned int Settings::get_width() const
{
	return this->width;
}

unsigned int Settings::get_height() const
{
	return this->height;
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

unsigned int Settings::get_max_acceleration() const
{
	return this->max_acceleration;
}

unsigned int Settings::get_max_velocity() const
{
	return this->max_velocity;
}

unsigned int Settings::get_grid_size() const
{
	return this->grid_size;
}

std::vector<particle_type> Settings::get_types() const
{
	return this->types;
}

std::vector<std::vector<float>> Settings::get_interactions() const
{
	return this->interactions;
}

std::vector<Particle> Settings::get_particles() const
{
	return this->particles;
}

/* ************************************************************************** */
