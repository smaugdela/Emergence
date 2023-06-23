#include "emergence.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Particle::Particle()
{
}

Particle::Particle(const particle_type type)
{
	_type = type;
	_vx = 0;
	_vy = 0;
	// Generate random coordinates for the particle between, 0 and GRID_SIZE;

	// std::default_random_engine generator;
	// std::uniform_int_distribution<int> distribution(0, my_settings.get_grid_size() - 1);
	// _x = distribution(generator);
	// _y = distribution(generator);

	// _x = read_urandom<int>() % my_settings.get_grid_size();
	// _y = read_urandom<int>() % my_settings.get_grid_size();

	_x = rand() % my_settings.get_grid_size();
	_y = rand() % my_settings.get_grid_size();

	_future_x = _x;
	_future_y = _y;
	_future_vx = _vx;
	_future_vy = _vy;
}

Particle::Particle(const Particle &src)
{
	*this = src;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Particle::~Particle()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Particle &Particle::operator=(Particle const &rhs)
{
	if (this != &rhs)
	{
		// Copy every attribute
		_x = rhs._x;
		_y = rhs._y;
		_vx = rhs._vx;
		_vy = rhs._vy;
		_type = rhs._type;
		_future_x = rhs._future_x;
		_future_y = rhs._future_y;
		_future_vx = rhs._future_vx;
		_future_vy = rhs._future_vy;
	}
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void Particle::compute()
{
	_future_x = _x;
	_future_y = _y;
	_future_vx = _vx;
	_future_vy = _vy;

	// Update the particle velocity
	// _future_vx += rand() % my_settings.get_max_acceleration() * (rand() % 2 ? 1 : -1);
	// _future_vy += rand() % my_settings.get_max_acceleration() * (rand() % 2 ? 1 : -1);

	// Update the particle velocity using actual interaction equation
	for (size_t i = 0; i < my_settings.get_particles().size(); i++)
	{
		Particle particleB = my_settings.get_particles()[i];
		if (&particleB == this)
			continue;

		unsigned int distance = std::sqrt(std::pow(particleB._x - _x, 2) + std::pow(particleB._y - _y, 2));

		if (distance == 0)
			continue;

		// Check if the particles are too close, and as such repell each other
		if (distance <= my_settings.get_particle_size() * 2)
		{
			unsigned int force = my_settings.get_max_acceleration() / distance;

			// Compute the interaction angle
			double angle = std::atan2(particleB._y - _y, particleB._x - _x);

			// Update the particle velocity
			_future_vx += -1.0 * static_cast<double>(force) * std::cos(angle);
			_future_vy += -1.0 * static_cast<double>(force) * std::sin(angle);
			continue;
		}

		// Check if the particles are close enough to interact
		if (distance > my_settings.get_grid_size() / 2)
			continue;

		// Compute the interaction force
		unsigned int force = my_settings.get_max_acceleration() / distance;

		// Compute the interaction angle
		double angle = std::atan2(particleB._y - _y, particleB._x - _x);

		// Update the particle velocity
		_future_vx += static_cast<double>(force) * std::cos(angle) * my_settings.get_interactions()[_type.id][particleB._type.id];
		_future_vy += static_cast<double>(force) * std::sin(angle) * my_settings.get_interactions()[_type.id][particleB._type.id];

		// std::cout << "force: " << force << "angle: " << angle << "cos(angle): " << std::cos(angle) << "sin(angle): " << std::sin(angle) << "interaction factor" << my_settings.get_interactions()[_type.id][particleB._type.id] << std::endl;
	}

	// Check velocity limits
	// if (static_cast<unsigned int>(std::abs(_future_vx)) > my_settings.get_max_velocity())
	// 	_future_vx = my_settings.get_max_velocity();
	// if (static_cast<unsigned int>(std::abs(_future_vy)) > my_settings.get_max_velocity())
	// 	_future_vy = my_settings.get_max_velocity();

	// Check friction and update velocity
	_future_vx = (_future_vx * (100 - my_settings.get_friction_coefficient())) / 100;
	_future_vy = (_future_vy * (100 - my_settings.get_friction_coefficient())) / 100;

	// Check wall collision
	if (_future_x + _future_vx < 0 || _future_x + _future_vx > static_cast<int>(my_settings.get_grid_size()))
		_future_vx = -_future_vx;
	if (_future_y + _future_vy < 0 || _future_y + _future_vy > static_cast<int>(my_settings.get_grid_size()))
		_future_vy = -_future_vy;

	// Update the future particle position
	_future_x += _future_vx;
	_future_y += _future_vy;

	// Check wall collision and teleport to the other side (continuous space)
	// if (_future_x < 0)
	// 	_future_x = my_settings.get_grid_size() - 1;
	// if (_future_x > static_cast<int>(my_settings.get_grid_size()))
	// 	_future_x = 0;
	// if (_future_y < 0)
	// 	_future_y = my_settings.get_grid_size() - 1;
	// if (_future_y > static_cast<int>(my_settings.get_grid_size()))
	// 	_future_y = 0;
}

void Particle::update()
{
	_x = _future_x;
	_y = _future_y;
	_vx = _future_vx;
	_vy = _future_vy;
}

void Particle::draw(sf::RenderWindow &window) const
{
	sf::CircleShape shape(my_settings.get_particle_size());

	// Need to transform the particle coordinates to the window coordinates
	float X, Y;
	X = ((float)_x / (float)my_settings.get_grid_size()) * (float)my_settings.get_width();
	Y = ((float)_y / (float)my_settings.get_grid_size()) * (float)my_settings.get_height();
	shape.setPosition(X, Y);

	shape.setFillColor(_type.color);

	window.draw(shape);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */
