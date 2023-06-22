#include "emergence.hpp"

Settings my_settings;

int main()
{
	// srand((unsigned int)time(NULL));

	sf::ContextSettings sfml_settings;
	sfml_settings.antialiasingLevel = my_settings.get_antialiasing_level();

	sf::RenderWindow window(sf::VideoMode(my_settings.get_width(), my_settings.get_height()), my_settings.get_title(), sf::Style::Default, sfml_settings);

	return loop(window);
}
