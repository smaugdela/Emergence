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

	int limit = int(my_settings.get_grid_size());
	_x = rand() % limit;
	_y = rand() % limit;

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

	float ax, ay = 0.f;

	// Update the particle velocity using actual interaction equation
	for (size_t i = 0; i < my_settings.get_particles().size(); i++)
	{
		Particle particleB = my_settings.get_particles()[i];
		if (&particleB == this)
			continue;

		float distance = std::pow(particleB._x - _x, 2) + std::pow(particleB._y - _y, 2);

		// Compute the interaction force
		float f = force(distance, my_settings.get_interactions()[_type.id][particleB._type.id]);

		// Compute the interaction angle
		double angle = std::atan2(particleB._y - _y, particleB._x - _x);

		// Update the particle velocity
		ax += f * std::cos(angle);
		ay += f * std::sin(angle);

		// std::cout << "force: " << force << "angle: " << angle << "cos(angle): " << std::cos(angle) << "sin(angle): " << std::sin(angle) << "interaction factor" << my_settings.get_interactions()[_type.id][particleB._type.id] << std::endl;
	}

	// Check friction and update velocity
	_future_vx = (_future_vx * (1 - my_settings.get_friction_coefficient())) + (ax * my_settings.get_delta_t());
	_future_vy = (_future_vy * (1 - my_settings.get_friction_coefficient())) + (ay * my_settings.get_delta_t());

	// Check wall collision
	if (_future_x + _future_vx < 0 || _future_x + _future_vx > static_cast<int>(my_settings.get_grid_size()))
		_future_vx = -_future_vx;
	if (_future_y + _future_vy < 0 || _future_y + _future_vy > static_cast<int>(my_settings.get_grid_size()))
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
