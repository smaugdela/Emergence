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
	this->_vz = 0.0f;

	// Generate random coordinates for the particle between, 0 and GRID_SIZE;
	int limit = int(my_settings.get_grid_size());
	this->_x = float(rand() % limit);
	this->_y = float(rand() % limit);
	if (my_settings.get_3d())
		this->_z = float(rand() % limit);
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
	for (std::vector<Particle *>::iterator it = particles.begin(); it != particles.end(); it++)
	{
		particleB = *it;
		if (*this == *particleB)
			continue;

		float distance, dx, dy, dz;
		dx = particleB->_x - _x;
		dy = particleB->_y - _y;
		dz = 0.0f;
		if (my_settings.get_3d())
		{
			distance = std::pow(particleB->_x - _x, 2) + std::pow(particleB->_y - _y, 2) + std::pow(particleB->_z - _z, 2);
			dz = particleB->_z - _z;
		}
		else
			distance = std::pow(particleB->_x - _x, 2) + std::pow(particleB->_y - _y, 2);

		if (distance > my_settings.get_max_range())
			continue;

		// Compute the interaction force
		float f = force(distance / my_settings.get_max_range(), interactions[_type.id][particleB->_type.id]);

		// Compute the interaction angle in 2D OLD
		// float angle = std::atan2(particleB->_y - _y, particleB->_x - _x);

		// Update the particle velocity OLD
		// ax += (f * std::cos(angle));
		// ay += (f * std::sin(angle));

		// Update the particle velocity
		ax += f * (dx / distance);
		ay += f * (dy / distance);
		if (my_settings.get_3d())
			az += f * (dz / distance);
	}

	// Check friction and update velocity
	_future_vx = (_future_vx * (1 - my_settings.get_friction_coefficient())) + (ax * my_settings.get_delta_t());
	_future_vy = (_future_vy * (1 - my_settings.get_friction_coefficient())) + (ay * my_settings.get_delta_t());
	if (my_settings.get_3d())
		_future_vz = (_future_vz * (1 - my_settings.get_friction_coefficient())) + (az * my_settings.get_delta_t());

	// Check wall collision
	if (_future_x + _future_vx < 0 || _future_x + _future_vx > my_settings.get_grid_size())
		_future_vx = -_future_vx;
	if (_future_y + _future_vy < 0 || _future_y + _future_vy > my_settings.get_grid_size())
		_future_vy = -_future_vy;
	if ((my_settings.get_3d()) && (_future_z + _future_vz < 0 || _future_z + _future_vz > my_settings.get_grid_size()))
		_future_vz = -_future_vz;

	// Update the future particle position
	_future_x += _future_vx;
	_future_y += _future_vy;
	if (my_settings.get_3d())
		_future_z += _future_vz;
}

void Particle::update()
{
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
	float X, Y;
	X = (_x / my_settings.get_grid_size()) * my_settings.get_width();
	Y = (_y / my_settings.get_grid_size()) * my_settings.get_height();
	shape.setPosition(X, Y);

	sf::Color color = _type.color;

	if (my_settings.get_3d())
	{
		// Setting the radius of the particle depending on its depth (far => small, close => big)
		float depth = _z - (my_settings.get_grid_size() / 2.f); // Depth is between 0 and grid_size
		shape.setRadius(my_settings.get_particle_size() * ((depth / my_settings.get_grid_size()) + 0.5f));

		// Setting the transparence of the particle depending on its depth (far => transparent, close => transparent, middle => opaque)
		color.a = static_cast<sf::Uint8>(200 * (1 - (std::abs(depth) / (my_settings.get_grid_size() / 2.f))) + 55);
	}

	shape.setFillColor(color);

	window.draw(shape);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */
