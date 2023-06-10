#ifndef PARTICLE_HPP
# define PARTICLE_HPP

# include <iostream>
# include <string>

class Particle
{

	public:

		Particle();
		Particle( Particle const & src );
		~Particle();

		Particle &		operator=( Particle const & rhs );

	private:

};

std::ostream &			operator<<( std::ostream & o, Particle const & i );

#endif /* ******************************************************** PARTICLE_H */