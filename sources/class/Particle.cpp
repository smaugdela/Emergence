#include "emergence.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Particle::Particle()
{
}

Particle::Particle(const particle_type type, const size_t id)
{
	this->_id = id;
	this->_type = type;
	this->_vx = 0.0f;
	this->_vy = 0.0f;

	// Generate random coordinates for the particle between, 0 and GRID_SIZE;
	int limit = int(my_settings.get_grid_size());
	this->_x = float(rand() % limit);
	this->_y = float(rand() % limit);

	this->_future_x = _x;
	this->_future_y = _y;
	this->_future_vx = _vx;
	this->_future_vy = _vy;
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
		this->_x = rhs._x;
		this->_y = rhs._y;
		this->_vx = rhs._vx;
		this->_vy = rhs._vy;
		this->_type = rhs._type;
		this->_future_x = rhs._future_x;
		this->_future_y = rhs._future_y;
		this->_future_vx = rhs._future_vx;
		this->_future_vy = rhs._future_vy;
	}
	return *this;
}

bool Particle::operator==(Particle const &rhs)
{
	return (this->_id == rhs._id);
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void Particle::compute(std::vector<Particle *> &particles, std::vector<std::vector<float>> &interactions)
{
	this->_future_x = _x;
	this->_future_y = _y;
	this->_future_vx = _vx;
	this->_future_vy = _vy;

	float ax, ay;
	ax = 0.0f;
	ay = 0.0f;

	Particle *particleB;

	// Update the particle velocity using actual interaction equation
	for (std::vector<Particle *>::iterator it = particles.begin(); it != particles.end(); it++)
	{
		particleB = *it;
		if (*this == *particleB)
			continue;

		float distance = std::pow(particleB->_x - _x, 2) + std::pow(particleB->_y - _y, 2);
		if (distance > my_settings.get_max_range())
			continue;

		// Compute the interaction force
		float f = force(distance / my_settings.get_max_range(), interactions[_type.id][particleB->_type.id]);

		// Compute the interaction angle
		float angle = std::atan2(particleB->_y - _y, particleB->_x - _x);

		// std::cout << "particleB->_y: " << particleB->_y << "particleB->_x: " << particleB->_x << "_y: " << _y << "_x: " << _x << std::endl;

		// Update the particle velocity
		ax += (f * std::cos(angle));
		ay += (f * std::sin(angle));

		// std::cout << "force: " << f << "angle: " << angle << "cos(angle): " << std::cos(angle) << "sin(angle): " << std::sin(angle) << "interaction factor" << interactions[_type.id][particleB->_type.id] << std::endl;
	}

	// Check friction and update velocity
	_future_vx = (_future_vx * (1 - my_settings.get_friction_coefficient())) + (ax * my_settings.get_delta_t());
	_future_vy = (_future_vy * (1 - my_settings.get_friction_coefficient())) + (ay * my_settings.get_delta_t());

	// Check wall collision
	if (_future_x + _future_vx < 0 || _future_x + _future_vx > my_settings.get_grid_size())
		_future_vx = -_future_vx;
	if (_future_y + _future_vy < 0 || _future_y + _future_vy > my_settings.get_grid_size())
		_future_vy = -_future_vy;

	// Update the future particle position
	_future_x += _future_vx;
	_future_y += _future_vy;
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
	X = (_x / my_settings.get_grid_size()) * my_settings.get_width();
	Y = (_y / my_settings.get_grid_size()) * my_settings.get_height();
	shape.setPosition(X, Y);

	shape.setFillColor(_type.color);

	window.draw(shape);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */
