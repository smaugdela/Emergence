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
	_x = rand() % GRID_SIZE;
	_y = rand() % GRID_SIZE;
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
	_vx += rand() % MAX_ACCELERATION * (rand() % 2 ? 1 : -1);
	_vy += rand() % MAX_ACCELERATION * (rand() % 2 ? 1 : -1);

	// Check velocity limits
	if (_vx > MAX_VELOCITY)
		_vx = MAX_VELOCITY;
	if (_vy > MAX_VELOCITY)
		_vy = MAX_VELOCITY;

	// Check wall collision
	if (_x + _vx < 0 || _x + _vx > GRID_SIZE)
		_vx = -_vx;
	if (_y + _vy < 0 || _y + _vy > GRID_SIZE)
		_vy = -_vy;

	// Update the particle position
	_x += _vx;
	_y += _vy;
}

void Particle::draw(sf::RenderWindow &window) const
{
	sf::CircleShape shape(PARTICLE_SIZE);

	// Need to transform the particle coordinates to the window coordinates
	float X, Y;
	X = ((float)_x / (float)GRID_SIZE) * (float)WIDTH;
	Y = ((float)_y / (float)GRID_SIZE) * (float)HEIGHT;
	shape.setPosition(X, Y);

	shape.setFillColor(sf::Color::Yellow);

	window.draw(shape);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */
