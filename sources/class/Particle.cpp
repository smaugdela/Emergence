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
	_x = rand() % my_settings.get_grid_size();
	_y = rand() % my_settings.get_grid_size();
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
	}
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void Particle::update()
{
	// Update the particle velocity
	_vx += rand() % my_settings.get_max_acceleration() * (rand() % 2 ? 1 : -1);
	_vy += rand() % my_settings.get_max_acceleration() * (rand() % 2 ? 1 : -1);

	// Check velocity limits
	if (static_cast<unsigned int>(std::abs(_vx)) > my_settings.get_max_velocity())
		_vx = my_settings.get_max_velocity();
	if (static_cast<unsigned int>(std::abs(_vy)) > my_settings.get_max_velocity())
		_vy = my_settings.get_max_velocity();

	// Check wall collision
	if (_x + _vx < 0 || _x + _vx > static_cast<int>(my_settings.get_grid_size()))
		_vx = -_vx;
	if (_y + _vy < 0 || _y + _vy > static_cast<int>(my_settings.get_grid_size()))
		_vy = -_vy;

	// Update the particle position
	_x += _vx;
	_y += _vy;
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
