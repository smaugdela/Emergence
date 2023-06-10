#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

struct particle_type
{
	size_t id;
	sf::Color color;
	// This vector contains the relations between the families.
	// The first element is the family id, the second is the force that is exerted between the two particle types.
	std::vector<int[2]> interactions;

} typedef particle_type;

class Particle
{

public:
	Particle();
	Particle(particle_type type);
	Particle(Particle const &src);
	Particle &operator=(Particle const &rhs);
	~Particle();

	// Update the particle position
	void update();

	// Draw the particle on the window
	void draw(sf::RenderWindow &window) const;

private:
	int _x;
	int _y;
	int _vx;
	int _vy;
	particle_type _type;
};

#endif /* ******************************************************** PARTICLE_H */
