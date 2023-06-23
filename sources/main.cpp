#include "emergence.hpp"

Settings my_settings;

int main(int ac, char **av)
{

	// Parse input arguments
	if (ac > 2)
	{
		std::cerr << "Usage: ./emergence [settings.json]" << std::endl;
		return EXIT_FAILURE;
	}
	if (ac == 2)
	{
		// Check if the user wants to display the help
		if (strcmp(av[1], "--help") == 0 || strcmp(av[1], "-h") == 0)
		{
			std::cout << "Usage: ./emergence [settings.json]" << std::endl;
			return EXIT_SUCCESS;
		}

		// Else, load settings from json file
		std::ifstream json_file(av[1]);
		if (!json_file)
		{
			std::cerr << "Error: could not open file " << av[1] << std::endl;
			return EXIT_FAILURE;
		}
		json json_settings = json::parse(json_file);
		my_settings.load_from_json(json_settings);
	}

	// Seed the random generator
	srand(time(0));

	// Set the antialiasing level
	sf::ContextSettings sfml_settings;
	sfml_settings.antialiasingLevel = my_settings.get_antialiasing_level();

	// Create the window
	sf::RenderWindow window(sf::VideoMode(my_settings.get_width(), my_settings.get_height()), my_settings.get_title(), sf::Style::Default, sfml_settings);

	return loop(window);
}
