#include "emergence.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Particle::Particle()
{
}

Particle::Particle(particle_type *type)
{
	this->_type = type;
	this->_vx = 0.0f;
	this->_vy = 0.0f;
	this->_vz = 0.0f;

	// Generate random coordinates for the particle between, 0 and GRID_SIZE;
	this->_x = float(rand() % int(my_settings.get_width()));
	this->_y = float(rand() % int(my_settings.get_height()));
	if (my_settings.get_3d())
		this->_z = float(rand() % int(my_settings.get_depth()));
	else
		this->_z = 0.0f;

	this->_future_x = _x;
	this->_future_y = _y;
	this->_future_z = _z;
	this->_future_vx = _vx;
	this->_future_vy = _vy;
	this->_future_vz = _vz;
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
		this->_z = rhs._z;
		this->_vx = rhs._vx;
		this->_vy = rhs._vy;
		this->_vz = rhs._vz;
		this->_type = rhs._type;
		this->_future_x = rhs._future_x;
		this->_future_y = rhs._future_y;
		this->_future_z = rhs._future_z;
		this->_future_vx = rhs._future_vx;
		this->_future_vy = rhs._future_vy;
		this->_future_vz = rhs._future_vz;
	}
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void Particle::compute(std::vector<std::vector<Particle *>> &particles, std::vector<std::vector<float>> &interactions)
{
	this->_future_x = _x;
	this->_future_y = _y;
	this->_future_z = _z;
	this->_future_vx = _vx;
	this->_future_vy = _vy;
	this->_future_vz = _vz;

	float ax, ay, az;
	ax = 0.0f;
	ay = 0.0f;
	az = 0.0f;

	Particle *particleB;

	// Update the particle velocity using actual interaction equation
	for (size_t i = 0; i < particles.size(); ++i)
	{
		for (std::vector<Particle *>::iterator it = particles[i].begin(); it != particles[i].end(); it++)
		{
			particleB = *it;
			if (this == particleB)
				continue;

			float distance;
			if (my_settings.get_3d())
				distance = std::pow(particleB->_x - _x, 2) + std::pow(particleB->_y - _y, 2) + std::pow(particleB->_z - _z, 2);
			else
				distance = std::pow(particleB->_x - _x, 2) + std::pow(particleB->_y - _y, 2);

			if (distance > my_settings.get_max_range())
				continue;

			particle_type *test = particleB->_type;
			size_t testid = test->id;
			size_t myid = _type->id;
			std::vector<float> test2 = interactions[myid];
			float test3 = test2[testid];
			(void)test3;

			// Compute the interaction force
			float f = force(distance / my_settings.get_max_range(), interactions[_type->id][particleB->_type->id]);

			if (my_settings.get_3d())
			{
				float dx, dy, dz;
				dx = particleB->_x - _x;
				dy = particleB->_y - _y;
				dz = particleB->_z - _z;
				ax += f * (dx / distance);
				ay += f * (dy / distance);
				az += f * (dz / distance);
			}
			else
			{
				float angle = std::atan2(particleB->_y - _y, particleB->_x - _x);
				ax += (f * std::cos(angle));
				ay += (f * std::sin(angle));
			}
		}
	}

	// Add temperature
	if (my_settings.get_temperature() > 0.f)
	{
		ax += float(rand() % 3 - 1) * my_settings.get_temperature() * my_settings.get_force_factor();
		ay += float(rand() % 3 - 1) * my_settings.get_temperature() * my_settings.get_force_factor();
		if (my_settings.get_3d())
			az += float(rand() % 3 - 1) * my_settings.get_temperature() * my_settings.get_force_factor();
	}

	// Check friction and update velocity
	_future_vx = (_future_vx * (1 - my_settings.get_friction_coefficient())) + (ax * my_settings.get_delta_t());
	_future_vy = (_future_vy * (1 - my_settings.get_friction_coefficient())) + (ay * my_settings.get_delta_t());
	if (my_settings.get_3d())
		_future_vz = (_future_vz * (1 - my_settings.get_friction_coefficient())) + (az * my_settings.get_delta_t());

	// Check wall collision
	if (_future_x + _future_vx < 0.f || _future_x + _future_vx >= my_settings.get_width())
		_future_vx = -_future_vx;
	if (_future_y + _future_vy < 0.f || _future_y + _future_vy >= my_settings.get_height())
		_future_vy = -_future_vy;
	if ((my_settings.get_3d()) && (_future_z + _future_vz < 0.f || _future_z + _future_vz >= my_settings.get_depth()))
		_future_vz = -_future_vz;

	// Update the future particle position
	_future_x += _future_vx;
	_future_y += _future_vy;
	if (my_settings.get_3d())
		_future_z += _future_vz;
}

void Particle::update()
{
	if (my_settings.get_pause())
		return;

	_x = _future_x;
	_y = _future_y;
	_z = _future_z;
	_vx = _future_vx;
	_vy = _future_vy;
	_vz = _future_vz;
}

void Particle::draw(sf::RenderWindow &window) const
{
	sf::CircleShape shape(my_settings.get_particle_size());

	// Need to transform the particle coordinates to the window coordinates
	// float X, Y;
	// X = (_x / my_settings.get_grid_size()) * my_settings.get_width();
	// Y = (_y / my_settings.get_grid_size()) * my_settings.get_height();
	// shape.setPosition(X, Y);
	shape.setPosition(_x, _y);

	sf::Color color = _type->color;

	if (my_settings.get_3d())
	{
		float depth = 2.f * _z / my_settings.get_depth(); // depth is between 0.f and 2.f

		// Setting the radius of the particle depending on its depth (far => small, close => big)
		shape.setRadius(std::pow(my_settings.get_particle_size(), depth));

		// Setting the transparence of the particle depending on its depth (far => transparent, close => opaque)
		color.a = static_cast<sf::Uint8>((90.f * depth) + 75.f);
	}

	// Take dopper effect into account
	if (my_settings.get_doppler_effect())
	{
		float speed;
		if (my_settings.get_3d())
			speed = std::pow(_vx, 2) + std::pow(_vy, 2) + std::pow(_vz, 2);
		else
			speed = std::pow(_vx, 2) + std::pow(_vy, 2);

		// float max_speed = std::pow(my_settings.get_width(), 2) + std::pow(my_settings.get_height(), 2);
		// float doppler = speed / max_speed;

		float doppler = speed / my_settings.get_doppler_factor();

		if (doppler > 1.f)
			doppler = 1.f;

		float rspan = 255.f - color.r;
		float gspan = color.g;
		float bspan = color.b;

		// The bigger doppler is, the more red the particle is
		color.r = static_cast<sf::Uint8>(color.r + (rspan * doppler));
		color.g = static_cast<sf::Uint8>(color.g - (gspan * doppler));
		color.b = static_cast<sf::Uint8>(color.b - (bspan * doppler));
	}

	shape.setFillColor(color);

	window.draw(shape);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

particle_type *Particle::get_type() const
{
	return _type;
}

/* ************************************************************************** */
