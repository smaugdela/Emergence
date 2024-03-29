#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

struct particle_type
{
	size_t id;
	sf::Color color;
	size_t amount;
} typedef particle_type;

class Particle
{

public:
	Particle();
	Particle(particle_type *type);
	Particle(Particle const &src);
	Particle &operator=(Particle const &rhs);
	~Particle();

	// Compute future state
	void compute(std::vector<std::vector<Particle *>> &particles, std::vector<std::vector<float>> &interactions);

	// Update the actual state to the future state
	void update();

	// Draw the particle on the window
	void draw(sf::RenderWindow &window) const;

	// Getters
	particle_type *get_type() const;

private:
	float _x;
	float _y;
	float _z;
	float _vx;
	float _vy;
	float _vz;
	float _future_x;
	float _future_y;
	float _future_z;
	float _future_vx;
	float _future_vy;
	float _future_vz;
	particle_type *_type;
};

#endif /* ******************************************************** PARTICLE_H */
