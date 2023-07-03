#include "emergence.hpp"

// Compute the force between two particles
float force(float r, float relation_coefficient)
{
	if (r < 0.f || r > 1.f)
		return 0;
	else if (r < my_settings.get_boundary_limit())
		return ((r / my_settings.get_boundary_limit() - 1.0f) * my_settings.get_force_factor());
	else
		return ((relation_coefficient * (1 - (std::fabs(2.f * r - 1.f - my_settings.get_boundary_limit()) / (1.f - my_settings.get_boundary_limit())))) * my_settings.get_force_factor());
}
