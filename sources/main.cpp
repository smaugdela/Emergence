#include "emergence.hpp"

Settings my_settings;

int main()
{
	sf::ContextSettings sfml_settings;
	sfml_settings.antialiasingLevel = my_settings.get_antialiasing_level();

	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(my_settings.get_width(), my_settings.get_height()), my_settings.get_title(), sf::Style::Default, sfml_settings);

	return loop(window);
}
