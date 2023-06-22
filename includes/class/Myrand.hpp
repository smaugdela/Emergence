#ifndef MYRAND_HPP
#define MYRAND_HPP

#include <fstream>
#include <cstdlib>

template <class T>
T read_urandom()
{
	union
	{
		T value;
		char cs[sizeof(T)];
	} u;

	std::ifstream rfin("/dev/urandom");
	rfin.read(u.cs, sizeof(u.cs));
	rfin.close();

	return u.value;
}

#endif
